#pragma once
#include "Window.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
enum D3D_FEATURE_LEVEL;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace Gumgine
{
	class D3D :	public Window
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
		ID3D11RenderTargetView* renderTargetView = nullptr;
		ID3D11DepthStencilView* depthStencilView = nullptr;

	public:
		D3D();
		virtual ~D3D() override;

	public:
		virtual bool SetDevice();
	};
}