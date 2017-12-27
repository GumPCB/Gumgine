#include "Core.h"
#include "../Util/Timer.h"

namespace Gumgine
{
	namespace Core
	{
		Core::Core()
		{
			SAFE_NEW( coreTimer , Gumgine::Util::Timer );
		}

		Core::~Core()
		{
			SAFE_DEL( coreTimer );
		}

		int Core::Run()
		{
			CoreInit();
			ShowWindow( GetHWND() , SW_SHOWDEFAULT );
			UpdateWindow( GetHWND() );

			MSG msg;
			ZeroMemory( &msg , sizeof( msg ) );
			while ( msg.message != WM_QUIT && this->isEnd != true )
			{
				if ( PeekMessage( &msg , GetHWND() , 0U , 0U , PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else
				{
					CoreFrame();
					CoreRender();
				}
				Sleep( 1 );
			}
			CoreRelease();
			return ( int ) msg.wParam;
		}

		bool Core::SetWin( const std::wstring& _titleName , unsigned int _width /*640*/ , unsigned int _height /*480*/ )
		{
			this->titleName = _titleName;
			this->width = _width;
			this->height = _height;
			return true;
		}

		// Init //////////////////////////////////////////////////////////////////////
		bool Core::CoreInit()
		{
			PreCoreInit();
			Init();
			PostCoreInit();
			return true;
		}

		//bool Core::Init()
		//{
		//	return true;
		//}

		bool Core::PreCoreInit()
		{
			SetWindow();
			SetDevice();
			coreTimer->Init();
			//I_Input.Init();
			//I_Xbox360Controller.Init();
			//I_CameraMgr.Init();
			//I_Debug.SetDebugMode( true );
			//I_Debug.Init();
			//m_pGumSky->Init();
			return true;
		}

		bool Core::PostCoreInit()
		{
			//I_LightMgr.Init();
			return true;
		}
		////////////////////////////////////////////////////////////////////// Init //

		// Frame /////////////////////////////////////////////////////////////////////
		bool Core::CoreFrame()
		{
			PreCoreFrame();
			Frame();
			PostCoreFrame();
			return true;
		}

		//bool Core::Frame()
		//{
		//	return true;
		//}

		bool Core::PreCoreFrame()
		{
			coreTimer->Frame();
			//I_Input.Frame();
			//I_Xbox360Controller.Frame();
			//I_Debug.Frame();
			//I_CameraMgr.Frame();
			return true;
		}

		bool Core::PostCoreFrame()
		{
			//I_LightMgr.Frame();
			//I_Input.SaveState();
			return true;
		}
		///////////////////////////////////////////////////////////////////// Frame //

		// Rander ////////////////////////////////////////////////////////////////////
		bool Core::CoreRender()
		{
			PreCoreRender();
			Render();
			PostCoreRender();
			return true;
		}

		//bool Core::Render()
		//{
		//	return true;
		//}

		bool Core::PreCoreRender()
		{
			//g_pd3dDevice->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 0 , 0 , 0 ) , 1.0f , 0 );
			//if ( FAILED( g_pd3dDevice->BeginScene() ) )
			//{
			//	return false;
			//}
			//m_pGumSky->Render();
			//I_Debug.Render();
			//I_LightMgr.Render();
			//I_CameraMgr.Render();
			return true;
		}

		bool Core::PostCoreRender()
		{
			//g_pd3dDevice->EndScene();
			//g_pd3dDevice->Present( NULL , NULL , NULL , NULL );
			return true;
		}
		//////////////////////////////////////////////////////////////////// Rander //

		// Release ///////////////////////////////////////////////////////////////////
		bool Core::CoreRelease()
		{
			PreCoreRelease();
			Release();
			return PostCoreRelease();
		}

		//bool Core::Release()
		//{
		//	return true;
		//}

		bool Core::PreCoreRelease()
		{
			return true;
		}

		bool Core::PostCoreRelease()
		{
			//I_Input.Release();
			//I_LightMgr.Release();
			//I_CameraMgr.Release();
			//I_Debug.Release();
			//m_pGumSky->Release();
			coreTimer->Release();
			D3D::Release();
			return true;
		}
		/////////////////////////////////////////////////////////////////// Release //
	}
}