#include "GeWindow.h"

namespace Gumgine
{
	HWND				g_hWnd;
	HINSTANCE			g_hInstance;

	DWORD				g_Screen_X_Size;
	DWORD				g_Screen_Y_Size;

	GeWindow* g_pWindow = NULL;

	LRESULT WINAPI gMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
	}

	LRESULT GeWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
			return 0;
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	bool GeWindow::SetWin(HINSTANCE hInst, TCHAR* pTitleName)
	{
		g_hInstance = hInst;
		UNREFERENCED_PARAMETER(hInst);

		// Register the window class
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_HREDRAW | CS_VREDRAW,//CS_CLASSDC,
			gMsgProc,
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
		SetRect(&rc, 0, 0, g_Screen_X_Size, g_Screen_Y_Size);
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		// Create the application's window
		m_hWnd = CreateWindow(L"GumCore_Ver100", pTitleName,
			WS_OVERLAPPEDWINDOW,
			0, 0,
			rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, wc.hInstance, NULL);

		g_hWnd = m_hWnd;

		return true;
	}

	void GeWindow::SetWindowRect(DWORD _dwWidth, DWORD _dwHeight)
	{
		g_Screen_X_Size = _dwWidth;
		g_Screen_Y_Size = _dwHeight;
	}

	GeWindow::GeWindow()
	{
		g_pWindow = this;
	}


	GeWindow::~GeWindow()
	{
	}

}