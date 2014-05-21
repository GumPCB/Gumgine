#include "D3D.h"
#include <D3D11.h>

namespace Gumgine
{
	D3D::D3D()
	{}


	D3D::~D3D()
	{}

	bool D3D::SetDevice()
	{
		// create d3d11 device
		unsigned int createDeviceFlags = 0;

# if defined ( DEBUG ) || defined ( _DEBUG )
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		HRESULT hr = D3D11CreateDevice( nullptr
										, D3D_DRIVER_TYPE_HARDWARE
										, nullptr
										, createDeviceFlags
										, nullptr
										, 0
										, D3D11_SDK_VERSION
										, &d3dDevice
										, &featureLevel
										, &d3dImmediateContext
										);

		if ( FAILED( hr ) )
		{
			MessageBox( nullptr , L"D3D11CreateDevice Failed." , nullptr , 0 );
			return false;
		}

		if ( featureLevel < D3D_FEATURE_LEVEL_11_0 )
		{
			MessageBox( nullptr , L"Direct3D Feature Level 11 unsupported." , nullptr , 0 );
			return false;
		}

		// Get 4xMSAA Quality
		HRESULT hrMsaa = d3dDevice->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM , 4 , &max4xMsaaQuality );
		assert( max4xMsaaQuality > 0 );
		if ( FAILED( hrMsaa ) )
		{
			MessageBox( nullptr , L"4xMSAA Quality Get Failed." , nullptr , 0 );
			return false;
		}

		// Set SWAP CHAIN
		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = GetWidth();
		sd.BufferDesc.Height = GetHeight();
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if ( enable4xMsaa )
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = max4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = GetHWND();
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		// Create SWAP CHAIN
		IDXGIDevice* dxgiDevice = nullptr;
		if ( FAILED( d3dDevice->QueryInterface( __uuidof( IDXGIDevice ) , ( void** ) &dxgiDevice ) ) )
		{
			MessageBox( nullptr , L"IDXGIDevice Failed." , nullptr , 0 );
			return false;
		}
		IDXGIAdapter* dxgiAdapter = nullptr;
		if ( FAILED( dxgiDevice->GetParent( __uuidof( IDXGIAdapter ) , ( void** ) &dxgiAdapter ) ) )
		{
			MessageBox( nullptr , L"IDXGIAdapter Failed." , nullptr , 0 );
			SAFE_RELEASE( dxgiDevice );
			return false;
		}
		IDXGIFactory* dxgiFactory = nullptr;
		if ( FAILED( dxgiAdapter->GetParent( __uuidof( IDXGIFactory ) , ( void** ) &dxgiFactory ) ) )
		{
			MessageBox( nullptr , L"IDXGIFactory Failed." , nullptr , 0 );
			SAFE_RELEASE( dxgiDevice );
			SAFE_RELEASE( dxgiAdapter );
			return false;
		}
		dxgiFactory->CreateSwapChain( d3dDevice , &sd , &swapChain );
		SAFE_RELEASE( dxgiDevice );
		SAFE_RELEASE( dxgiAdapter );
		SAFE_RELEASE( dxgiFactory );

		// Create RenderTarget View
		ID3D11Texture2D* backBuffer = nullptr;
		swapChain->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , reinterpret_cast< void** >( &backBuffer ) );
		d3dDevice->CreateRenderTargetView( backBuffer , 0 , &renderTargetView );
		SAFE_RELEASE( backBuffer );

		// Create DepthStencil View
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = GetWidth();
		depthStencilDesc.Height = GetHeight();
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if ( enable4xMsaa )
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = max4xMsaaQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}

		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		ID3D11Texture2D* depthStencilBuffer = nullptr;
		d3dDevice->CreateTexture2D( &depthStencilDesc , 0 , &depthStencilBuffer );
		d3dDevice->CreateDepthStencilView( depthStencilBuffer , 0 , &depthStencilView );

		// Set RenderTargets
		d3dImmediateContext->OMSetRenderTargets( 1 , &renderTargetView , depthStencilView );

		// Set ViewPorts
		D3D11_VIEWPORT vp = { 0.0f , 0.0f , static_cast< float >( GetWidth() ) , static_cast< float >( GetHeight() ) , 0.0f , 1.0f };
		d3dImmediateContext->RSSetViewports( 1 , &vp );

		return true;
	}
}