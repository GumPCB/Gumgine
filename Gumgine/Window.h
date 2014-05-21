#pragma once
#include "GeStd.h"

namespace Gumgine
{
	class Window
	{
	protected:
		HWND			hWnd = nullptr;
		HINSTANCE		hInstance = nullptr;
		unsigned int	width = 640;
		unsigned int	height = 480;

	public:
		Window();
		virtual ~Window();

	public:
		bool			SetWin( HINSTANCE hInst , TCHAR* pTitleName );
		void			SetWindowSize( DWORD width , DWORD height );
		int				Run();

		const HWND		GetHWND() const { return hWnd; }
		const int		GetWidth() const { return width; }
		const int		GetHeight() const { return height; }

	};
}