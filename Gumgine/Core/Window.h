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
			HINSTANCE		hInstance = ( HINSTANCE ) GetModuleHandle( NULL );
			unsigned int	width = 640;
			unsigned int	height = 480;
			std::wstring	titleName;
			bool			isEnd = false;
			bool			isActive = true;

		public:
			explicit Window();
			virtual ~Window();

		public:
			virtual bool	SetWin( const std::wstring& _titleName , unsigned int _width = 640 , unsigned int _height = 480 );
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