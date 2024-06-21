#include "pch.h"
#include "Window.h"
#include "../Singleton/BasicSingleton.h"
#include "../Singleton/Global.h"

namespace Gumgine
{
	namespace Core
	{
		Window::Window()
		{
			Singleton::ThreadSingleton< Window >::GetInstance().SetPtr( this );
		}

		Window::~Window()
		{
			Singleton::ThreadSingleton< Window >::GetInstance().Clear();
		}

		bool Window::SetWin( const std::wstring& _titleName , unsigned int _width /*640*/ , unsigned int _height /*480*/ )
		{
			this->titleName = _titleName;
			this->width = _width;
			this->height = _height;
			
			return SetWindow();
		}

		//void Window::SetWindowSize( DWORD width , DWORD height )
		//{
		//	
		//}

		LRESULT Window::MsgProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )
		{
			switch ( msg )
			{
				case WM_DESTROY:
				{
					isEnd = true;
					PostQuitMessage( 0 );
					return 0;
				}
				case WM_CLOSE:
				{
					DestroyWindow( hwnd );
					return 0;
				}
				case WM_ACTIVATE:
				{
					if ( LOWORD( wParam ) == WA_INACTIVE )
					{
						isActive = false;
					}
					else
					{
						isActive = true;
					}
					return 0;
				}
				default:
				break;
			}
			return DefWindowProc( hwnd , msg , wParam , lParam );
		}

		bool Window::SetWindow()
		{
			UNREFERENCED_PARAMETER( hInstance );

			// Register the window class
			WNDCLASSEX wc =
			{
				sizeof( WNDCLASSEX )
				, CS_HREDRAW | CS_VREDRAW	//CS_CLASSDC
				, []( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )->LRESULT
				{
					auto win = Singleton::ThreadSingleton< Window >::GetInstance().GetPtr();
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
			this->hWnd = CreateWindow( wc.lpszClassName , titleName.c_str()
									   , WS_OVERLAPPEDWINDOW
									   , 0 , 0
									   , rc.right - rc.left , rc.bottom - rc.top
									   , nullptr
									   , nullptr
									   , wc.hInstance
									   , nullptr
									   );

			if ( this->hWnd == nullptr )
			{
				MessageBox( nullptr, L"CreateWindow Failed.", nullptr, 0 );
				return false;
			}
			return true;
		}
	}
}