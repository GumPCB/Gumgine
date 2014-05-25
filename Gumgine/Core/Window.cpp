#include "Window.h"
#include "../Singleton/Singleton.h"

namespace Gumgine
{
	namespace Core
	{
		Window::Window()
		{
			Gumgine::Singleton::GlobalVariables::GetInstance().SetWindow( this );
		}

		Window::~Window()
		{
			Gumgine::Singleton::GlobalVariables::GetInstance().SetWindow( nullptr );
		}

		bool Window::SetWin( HINSTANCE hInst , TCHAR* pTitleName , unsigned int width /*640*/ , unsigned int height /*480*/ )
		{
			this->width = width;
			this->height = height;

			hInstance = hInst;
			UNREFERENCED_PARAMETER( hInst );

			// Register the window class
			WNDCLASSEX wc =
			{
				sizeof( WNDCLASSEX )
				, CS_HREDRAW | CS_VREDRAW	//CS_CLASSDC
				, []( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )->LRESULT 
				{
					auto win = Gumgine::Singleton::GlobalVariables::GetInstance().GetWindow();
					if ( win != nullptr )
					{
						return win->MsgProc( hwnd , msg , wParam , lParam );
					}
					return NULL;
				}
				, 0
				, 0
				, hInstance//GetModuleHandle( nullptr )
				, nullptr
				, nullptr
				, nullptr	//(HBRUSH)GetStockObject(WHITE_BRUSH)
				, nullptr
				, L"Gumgine_Ver0.01"
				, nullptr
			};
			RegisterClassEx( &wc );

			RECT rc;
			SetRect( &rc , 0 , 0 , width , height );
			AdjustWindowRect( &rc , WS_OVERLAPPEDWINDOW , false );

			// Create the application's window
			this->hWnd = CreateWindow( wc.lpszClassName , pTitleName
									   , WS_OVERLAPPEDWINDOW
									   , 0 , 0
									   , rc.right - rc.left , rc.bottom - rc.top
									   , nullptr
									   , nullptr
									   , wc.hInstance
									   , nullptr
									   );

			return true;
		}

		//void Window::SetWindowSize( DWORD width , DWORD height )
		//{
		//	
		//}

		int	Window::Run()
		{
			ShowWindow( GetHWND() , SW_SHOWDEFAULT );
			UpdateWindow( GetHWND() );

			MSG msg;
			ZeroMemory( &msg , sizeof( msg ) );
			while ( msg.message != WM_QUIT )
			{
				if ( PeekMessage( &msg , nullptr , 0U , 0U , PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else
				{
					//랜더랑 같은 코드로 프레임
				}
			}
			return ( int ) msg.wParam;
		}

		LRESULT Window::MsgProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )
		{
			switch ( msg )
			{
				case WM_DESTROY:
				{
					PostQuitMessage( 0 );
				}
				return 0;
				case WM_CLOSE:
				{
					PostQuitMessage( 0 );
				}
				return 0;
			}
			return DefWindowProc( hwnd , msg , wParam , lParam );
		}
	}
}