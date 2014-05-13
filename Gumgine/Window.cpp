#include "Window.h"

namespace Gumgine
{
	bool Window::SetWin(HINSTANCE hInst, TCHAR* pTitleName)
	{
		hInstance = hInst;
		UNREFERENCED_PARAMETER(hInst);

		// Register the window class
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_HREDRAW | CS_VREDRAW,//CS_CLASSDC,
			msgProc,
			0L,
			0L,
			GetModuleHandle(NULL),
			NULL,
			NULL,
			NULL,//(HBRUSH)GetStockObject(WHITE_BRUSH),
			NULL,
			L"GumCore_Ver100", NULL
		};
		RegisterClassEx(&wc);

		RECT rc;
		SetRect(&rc, 0, 0, width, height);
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		// Create the application's window
		hWnd = CreateWindow(L"Gumgine_Ver0.01", pTitleName,
			WS_OVERLAPPEDWINDOW,
			0, 0,
			rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, wc.hInstance, NULL
			);

		return true;
	}

	void Window::SetWindowSize(DWORD width, DWORD height)
	{
		this->width = width;
		this->height = height;
	}

	Window::Window()
	{
	}

	Window::~Window()
	{
	}
}