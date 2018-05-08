#pragma once
#include "..\..\Common\d3dx12.h"
#include "..\..\Common\d3dUtil.h"
#include "Window.h"
#include <codecvt>
class D3DException : public std::exception
{
	public:
	D3DException( HRESULT hr, const char* fileName, int line, const char* funcName )
	{
		std::ios::fmtflags flags = reason.flags();
		reason << "HRESULT : 0x" << std::hex << hr;
		reason.setf( flags );
		reason << ", File : " << fileName
			<< "(" << line << "), Func : " << funcName << "\n";
		OutputDebugStringA( reason.str().c_str() );
		_com_error err( hr );
		OutputDebugString( err.ErrorMessage() );
	}
	virtual const char* what() const override
	{
		return reason.str().c_str();
	}
	private:
	std::stringstream reason;
};

#define ThrowIfFailed( X )														\
{																				\
	HRESULT hr = ( X );															\
	if ( FAILED( hr ) ) { throw D3DException( hr, __FILE__, __LINE__, #X ); }	\
}

namespace Gumgine
{
	namespace Core
	{
		class D3D : public Window
		{
		protected:
			// D3D12
			Microsoft::WRL::ComPtr< ID3D12Device > d3dDevice;
			Microsoft::WRL::ComPtr< IDXGIFactory4 > dxgiFactory;
			Microsoft::WRL::ComPtr< IDXGISwapChain > swapChain;

			Microsoft::WRL::ComPtr< ID3D12Fence > fence;
			unsigned __int64 currentFence = 0;

			Microsoft::WRL::ComPtr< ID3D12CommandQueue > commandQueue;
			Microsoft::WRL::ComPtr< ID3D12CommandAllocator > commandAllocator;
			Microsoft::WRL::ComPtr< ID3D12GraphicsCommandList > commandList;

			Microsoft::WRL::ComPtr< ID3D12DescriptorHeap > rtvHeap;
			Microsoft::WRL::ComPtr< ID3D12DescriptorHeap > dsvHeap;

			static const int swapChainBufferCount = 2;
			int currentBackBuffer = 0;

			Microsoft::WRL::ComPtr< ID3D12Resource > swapChainBuffer[ swapChainBufferCount ];
			Microsoft::WRL::ComPtr< ID3D12Resource > depthStencilBuffer;

			unsigned int rtvDescriptorSize = 0;
			unsigned int dsvDescriptorSize = 0;
			unsigned int cbvSrvDescriptorSize = 0;

			// MSAA
			unsigned int msaaQuality = 0;
			bool enableMsaa = false;

			DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

			D3D12_VIEWPORT viewPort;
			D3D12_RECT scissorRect;

		public:
			D3D();
			virtual ~D3D() override;

		protected:
			virtual bool SetDevice();
			virtual void Resize();

			void CreateCommandObjects();
			void CreateSwapChain();
			void CreateRtvAndDsvDescriptorHeaps();

			void FlushCommandQueue();

			ID3D12Resource* CurrentBackBuffer() const;
			D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
			D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

			void LogAdapters();
			void LogAdapterOutputs( IDXGIAdapter* adapter );
			void LogOutputDisplayModes( IDXGIOutput* output, DXGI_FORMAT format );

			bool Release();
		};
	}
}