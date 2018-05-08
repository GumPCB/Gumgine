#include "D3D.h"

#include <codecvt>


namespace Gumgine
{
	namespace Core
	{
		D3D::D3D()
		{
		}

		D3D::~D3D()
		{
			if ( d3dDevice != nullptr )
			{
				FlushCommandQueue();
			}
		}

		bool D3D::SetDevice()
		{
			// SetDevice는 한번에 하나씩
			static std::mutex mutex;
			std::lock_guard< std::mutex > lock( mutex );

			// create d3d12 device
#if defined ( DEBUG ) || defined ( _DEBUG )
			Microsoft::WRL::ComPtr< ID3D12Debug > debugController;
			ThrowIfFailed( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) );
			debugController->EnableDebugLayer();
#endif
			ThrowIfFailed( CreateDXGIFactory1( IID_PPV_ARGS( &dxgiFactory ) ) );

			HRESULT hrCreateDevice = D3D12CreateDevice( nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS( &d3dDevice ) );

			if ( FAILED( hrCreateDevice ) )
			{
				Microsoft::WRL::ComPtr< IDXGIAdapter > warpAdapter;
				ThrowIfFailed( dxgiFactory->EnumWarpAdapter( IID_PPV_ARGS( &warpAdapter ) ) );

				ThrowIfFailed( D3D12CreateDevice( warpAdapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS( &d3dDevice ) ) );
			}
			
			// create Fence
			ThrowIfFailed( d3dDevice->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &fence ) ) );
			rtvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
			dsvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
			cbvSrvDescriptorSize = d3dDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

			// MSAA
			D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels;
			msaaQualityLevels.Format = backBufferFormat;
			msaaQualityLevels.SampleCount = 4;
			msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
			msaaQualityLevels.NumQualityLevels = 0;
			ThrowIfFailed( d3dDevice->CheckFeatureSupport( D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityLevels, sizeof( msaaQualityLevels ) ) );

			msaaQuality = msaaQualityLevels.NumQualityLevels;
			assert( msaaQuality > 0 && "Unexpected MSAA quality level." );

#if defined ( DEBUG ) || defined ( _DEBUG )
			LogAdapters();
#endif

			// Command List, SwapChain, RenderTargetView, DrpthStencilView
			CreateCommandObjects();
			CreateSwapChain();
			CreateRtvAndDsvDescriptorHeaps();
			return true;
		}

		void D3D::Resize()
		{
			assert( d3dDevice );
			assert( swapChain );
			assert( commandAllocator );

			FlushCommandQueue();

			ThrowIfFailed( commandList->Reset( commandAllocator.Get(), nullptr ) );

			for ( int i = 0 ; i < swapChainBufferCount ; ++i )
			{
				swapChainBuffer[ i ].Reset();
			}
			depthStencilBuffer.Reset();

			ThrowIfFailed( swapChain->ResizeBuffers( swapChainBufferCount, GetWidth(), GetHeight(), backBufferFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ) );
			currentBackBuffer = 0;

			// RenderTargetView
			CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle( rtvHeap->GetCPUDescriptorHandleForHeapStart() );
			for ( int i = 0 ; i < swapChainBufferCount ; ++i )
			{
				ThrowIfFailed( swapChain->GetBuffer( i, IID_PPV_ARGS( &swapChainBuffer[ i ] ) ) );
				d3dDevice->CreateRenderTargetView( swapChainBuffer[ i ].Get(), nullptr, rtvHeapHandle );
				rtvHeapHandle.Offset( 1, rtvDescriptorSize );
			}

			// DrpthStencilView
			D3D12_RESOURCE_DESC depthStencilDesc;
			depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			depthStencilDesc.Alignment = 0;
			depthStencilDesc.Width = GetWidth();
			depthStencilDesc.Height = GetHeight();
			depthStencilDesc.DepthOrArraySize = 1;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.Format = depthStencilFormat;
			depthStencilDesc.SampleDesc.Count = enableMsaa ? 4 : 1;
			depthStencilDesc.SampleDesc.Quality = enableMsaa ? ( msaaQuality - 1 ) : 0;
			depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

			D3D12_CLEAR_VALUE clearValue;
			clearValue.Format = depthStencilFormat;
			clearValue.DepthStencil.Depth = 1.0f;
			clearValue.DepthStencil.Stencil = 0;

			CD3DX12_HEAP_PROPERTIES heapProperties( D3D12_HEAP_TYPE_DEFAULT );
			ThrowIfFailed( d3dDevice->CreateCommittedResource( &heapProperties
						   , D3D12_HEAP_FLAG_NONE
						   , &depthStencilDesc
						   , D3D12_RESOURCE_STATE_COMMON
						   , &clearValue
						   , IID_PPV_ARGS( depthStencilBuffer.GetAddressOf() ) ) );

			d3dDevice->CreateDepthStencilView( depthStencilBuffer.Get(), nullptr, DepthStencilView() );

			// ResourceBarrier
			auto resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition( depthStencilBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE );
			commandList->ResourceBarrier( 1, &resourceBarrier );

			ThrowIfFailed( commandList->Close() );
			ID3D12CommandList* commandLists[] = { commandList.Get() };
			commandQueue->ExecuteCommandLists( _countof( commandLists ), commandLists );

			FlushCommandQueue();

			// ViewPort
			viewPort.TopLeftX = 0.0f;
			viewPort.TopLeftY = 0.0f;
			viewPort.Width = static_cast< float >( GetWidth() );
			viewPort.Height = static_cast< float >( GetHeight() );
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;

			scissorRect = { 0, 0, GetWidth(), GetHeight() };
		}

		void D3D::CreateCommandObjects()
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc = {};
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

			ThrowIfFailed( d3dDevice->CreateCommandQueue( &queueDesc, IID_PPV_ARGS( &commandQueue ) ) );
			ThrowIfFailed( d3dDevice->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( commandAllocator.GetAddressOf() ) ) );
			ThrowIfFailed( d3dDevice->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS( commandList.GetAddressOf() ) ) );

			commandList->Close();
		}

		void D3D::CreateSwapChain()
		{
			swapChain.Reset();

			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			swapChainDesc.BufferDesc.Width = GetWidth();
			swapChainDesc.BufferDesc.Height = GetHeight();
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferDesc.Format = backBufferFormat;
			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			swapChainDesc.SampleDesc.Count = enableMsaa ? 4 : 1;
			swapChainDesc.SampleDesc.Quality = enableMsaa ? ( msaaQuality - 1 ) : 0;

			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = swapChainBufferCount;
			swapChainDesc.OutputWindow = GetHWND();
			swapChainDesc.Windowed = true;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			ThrowIfFailed( dxgiFactory->CreateSwapChain( commandQueue.Get(), &swapChainDesc, swapChain.GetAddressOf() ) );
		}

		void D3D::CreateRtvAndDsvDescriptorHeaps()
		{
			D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
			rtvHeapDesc.NumDescriptors = swapChainBufferCount;
			rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			rtvHeapDesc.NodeMask = 0;
			ThrowIfFailed( d3dDevice->CreateDescriptorHeap( &rtvHeapDesc, IID_PPV_ARGS( rtvHeap.GetAddressOf() ) ) );

			D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
			dsvHeapDesc.NumDescriptors = 1;
			dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
			dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			dsvHeapDesc.NodeMask = 0;
			ThrowIfFailed( d3dDevice->CreateDescriptorHeap( &dsvHeapDesc, IID_PPV_ARGS( dsvHeap.GetAddressOf() ) ) );
		}

		void D3D::FlushCommandQueue()
		{
			++currentFence;
			ThrowIfFailed( commandQueue->Signal( fence.Get(), currentFence ) );

			if ( fence->GetCompletedValue() < currentFence )
			{
				HANDLE eventHandle = CreateEventEx( nullptr, false, false, EVENT_ALL_ACCESS );
				ThrowIfFailed( fence->SetEventOnCompletion( currentFence, eventHandle ) );
				WaitForSingleObject( eventHandle, INFINITE );
				CloseHandle( eventHandle );
			}
		}

		ID3D12Resource * D3D::CurrentBackBuffer() const
		{
			return swapChainBuffer[ currentBackBuffer ].Get();
		}

		D3D12_CPU_DESCRIPTOR_HANDLE D3D::CurrentBackBufferView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE( rtvHeap->GetCPUDescriptorHandleForHeapStart(), currentBackBuffer, rtvDescriptorSize );
		}

		D3D12_CPU_DESCRIPTOR_HANDLE D3D::DepthStencilView() const
		{
			return dsvHeap->GetCPUDescriptorHandleForHeapStart();
		}

		void D3D::LogAdapters()
		{
			unsigned int i = 0;
			IDXGIAdapter* adapter = nullptr;
			std::vector< IDXGIAdapter* > adapterList;
			while ( dxgiFactory->EnumAdapters( i++, &adapter ) != DXGI_ERROR_NOT_FOUND )
			{
				DXGI_ADAPTER_DESC desc;
				adapter->GetDesc( &desc );

				std::wstring text = L"**adapter : ";
				text += desc.Description;
				text += L"\n";

				OutputDebugString( text.c_str() );
				adapterList.push_back( adapter );
			}

			for ( auto itr : adapterList )
			{
				LogAdapterOutputs( itr );
				ReleaseCom( itr );
			}
		}

		void D3D::LogAdapterOutputs( IDXGIAdapter * adapter )
		{
			unsigned int i = 0;
			IDXGIOutput* output = nullptr;
			while ( adapter->EnumOutputs( i++, &output ) != DXGI_ERROR_NOT_FOUND )
			{
				DXGI_OUTPUT_DESC desc;
				output->GetDesc( &desc );

				std::wstring text = L"**Output : ";
				text += desc.DeviceName;
				text += L"\n";

				OutputDebugString( text.c_str() );
				LogOutputDisplayModes( output, backBufferFormat );

				ReleaseCom( output );
			}
		}

		void D3D::LogOutputDisplayModes( IDXGIOutput * output, DXGI_FORMAT format )
		{
			unsigned int count = 0;
			unsigned int flags = 0;

			output->GetDisplayModeList( format, flags, &count, nullptr );

			std::vector< DXGI_MODE_DESC > modeList( count );
			output->GetDisplayModeList( format, flags, &count, &modeList[ 0 ] );

			for ( auto& itr : modeList )
			{
				std::wstring text = L"Width : " + std::to_wstring( itr.Width ) + L" " +
					L"Height : " + std::to_wstring( itr.Height ) + L" " +
					L"Refresh : " + std::to_wstring( itr.RefreshRate.Numerator ) +
					L"/" + std::to_wstring( itr.RefreshRate.Denominator ) + L"\n";
				
				OutputDebugString( text.c_str() );
			}
		}

		bool D3D::Release()
		{
			return true;
		}
	}
}