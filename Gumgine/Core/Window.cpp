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

		bool Window::SetWin( HINSTANCE hInst , const std::wstring& titleName , unsigned int width /*640*/ , unsigned int height /*480*/ )
		{
			this->titleName = titleName;
			this->width = width;
			this->height = height;
			this->hInstance = hInst;
			IF_FALSE_RETURN_FALSE( SetWindow() );
			return true;
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
				}
				return 0;
				case WM_CLOSE:
				{
					isEnd = true;
					PostQuitMessage( 0 );
				}
				return 0;
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
			this->hWnd = CreateWindow( wc.lpszClassName , titleName.c_str()
									   , WS_OVERLAPPEDWINDOW
									   , 0 , 0
									   , rc.right - rc.left , rc.bottom - rc.top
									   , nullptr
									   , nullptr
									   , wc.hInstance
									   , nullptr
									   );
			IF_NULL_MSGBOX_RETURN_FALSE( this->hWnd , L"CreateWindow Failed." );
			return true;
		}
	}
}