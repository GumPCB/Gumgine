#pragma once
#include "Window.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
enum D3D_FEATURE_LEVEL;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct D3D11_VIEWPORT;

namespace Gumgine
{
	namespace Core
	{
		class D3D : public Window
		{
		protected:
			// D3D11
			ID3D11Device* d3dDevice = nullptr;
			ID3D11DeviceContext* d3dImmediateContext = nullptr;
			D3D_FEATURE_LEVEL featureLevel;

			// 4xMSAA
			unsigned int	max4xMsaaQuality = 0;
			bool			enable4xMsaa = true;

			// IDXGISwapChain
			IDXGISwapChain* swapChain = nullptr;

			// Render Target View
			ID3D11Texture2D* depthStencilBuffer = nullptr;
			ID3D11RenderTargetView* renderTargetView = nullptr;
			ID3D11DepthStencilView* depthStencilView = nullptr;

			D3D11_VIEWPORT* screenViewPort = nullptr;

		public:
			D3D();
			virtual ~D3D() override;

		protected:
			virtual bool SetDevice();
			virtual bool Release();
		};
	}
}