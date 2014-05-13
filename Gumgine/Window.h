#pragma once
#include "GeStd.h"

namespace Gumgine
{
	class Window
	{
	public:
		Window();
		virtual ~Window();

	public:
		bool			SetWin(HINSTANCE hInst, TCHAR* pTitleName);
		void			SetWindowSize(DWORD width, DWORD height);

		const HWND		GetHWND() const { return hWnd; }

	private:
		HWND		hWnd = nullptr;
		HINSTANCE	hInstance = nullptr;
		DWORD		width = 640;
		DWORD		height = 480;
		WNDPROC		msgProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT
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
					};
	};
}