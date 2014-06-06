#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Core
	{
		// 윈도우 클래스, 스레드 하나당 하나씩만 사용해야 함
		class Window
		{
		protected:
			HWND			hWnd = nullptr;
			HINSTANCE		hInstance = nullptr;
			unsigned int	width = 640;
			unsigned int	height = 480;
			std::wstring	titleName;
			bool			isEnd = false;

		public:
			Window();
			virtual ~Window();

		public:
			virtual bool	SetWin( HINSTANCE hInst , const std::wstring& titleName , unsigned int width = 640 , unsigned int height = 480 );
			//void			SetWindowSize( DWORD width , DWORD height );
			virtual LRESULT MsgProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );

			const HWND		GetHWND() const { return hWnd; }
			const int		GetWidth() const { return width; }
			const int		GetHeight() const { return height; }

		protected:
			virtual bool	SetWindow();

		};
	}
}