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
		bool			SetWin( HINSTANCE hInst , TCHAR* pTitleName );
		void			SetWindowSize( DWORD width , DWORD height );
		int				Run();

		const HWND		GetHWND() const { return this->hWnd; }

	private:
		HWND		hWnd = nullptr;
		HINSTANCE	hInstance = nullptr;
		DWORD		width = 640;
		DWORD		height = 480;
	};
}