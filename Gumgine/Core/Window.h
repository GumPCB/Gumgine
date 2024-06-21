#pragma once

namespace Gumgine
{
	namespace Core
	{
		// 윈도우 클래스
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

			const HWND		GetHWND() const noexcept { return hWnd; }
			const int		GetWidth() const noexcept { return width; }
			const int		GetHeight() const noexcept { return height; }

		protected:
			virtual bool	SetWindow();

		};
	}
}