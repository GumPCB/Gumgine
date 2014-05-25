#pragma once
#include "../GeStd.h"

namespace Gumgine
{
	namespace Core
	{
		// ������ Ŭ����, ������ �ϳ��� �ϳ����� ����ؾ� ��
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
			bool			SetWin( HINSTANCE hInst , TCHAR* pTitleName , unsigned int width = 640 , unsigned int height = 480 );
			//void			SetWindowSize( DWORD width , DWORD height );
			int				Run();
			virtual LRESULT MsgProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );

			const HWND		GetHWND() const { return hWnd; }
			const int		GetWidth() const { return width; }
			const int		GetHeight() const { return height; }

		};
	}
}