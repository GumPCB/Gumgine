#pragma once
#include "D3D.h"

#define SAFE_ZERO( Var )					{ Var = 0; }
#define SAFE_NEW( Var , Type )				{ if( Var == nullptr ) Var = new Type; }
#define SAFE_DEL( Var )						{ if( Var != nullptr ) delete Var; ( Var ) = nullptr; }
#define SAFE_ARRAY_NEW( Var , Type , Num )	{ if( Var == nullptr && Num > 0 ) Var = new Type[Num]; }
#define SAFE_ARRAY_DEL( Var )				{ if( Var != nullptr ) delete [] Var; ( Var ) = nullptr; }
#define SAFE_RELEASE( Object )				{ if( Object != nullptr ) { ( Object )->Release(); ( Object ) = nullptr; } }
#define NEW_CLEAR( Var , Type )				{ if( Var == nullptr ) Var = new Type(); if( Var != nullptr ) memset( Var, 0, sizeof( Type ) ); }
#define NEW_ARRAY_CLEAR( Var , Type , Num )	{ if( Var == nullptr && Num > 0 ) Var = new Type[ Num ]; if( Var != nullptr ) memset( Var, 0, sizeof( Type ) * Num ); }
#define SAFE_STL_CONTAINER_DELETE( Var )	{ for ( auto iter = Var.begin() ; iter != Var.end() ; ++iter ) SAFE_DEL( *iter ); }

//#define TEX_PATH_WCHAR				L"..\\data\\TEX\\"

//extern DWORD				g_Screen_X_Size;
//extern DWORD				g_Screen_Y_Size;
//extern bool					g_bSkyBox;
//extern float				g_fSecPerFrame;
//extern LPDIRECT3DDEVICE9	g_pd3dDevice;
//extern HWND					g_hWnd;
//extern HINSTANCE			g_hInstance;
//
//typedef basic_string<TCHAR>				TCHAR_STRING;
//typedef vector< basic_string<TCHAR> >	TCHAR_STRING_VECTOR;
//typedef vector<D3DXVECTOR3>				D3DXVECTOR3_VECTOR;
//typedef list<DWORD>						DWORD_LIST;

namespace Gumgine
{
	namespace Util
	{
		class FPSCounter;
	}
	namespace Core
	{
		class IRenderable
		{
		public:
			virtual bool Init() = 0;	// �ʱ�ȭ
			virtual bool Frame() = 0;	// �׸��� ���� ����
			virtual bool Render() = 0;	// ȭ�鿡 �׸���
			virtual bool Release() = 0; // �ڿ� ����
		};

		class IManagedRenderable : IRenderable
		{
		public:
			virtual ~IManagedRenderable() {};
			virtual bool Init() override = 0;						// �ʱ�ȭ
			virtual bool Frame() override = 0;						// �׸��� ���� ����
			virtual bool Render() override = 0;						// ȭ�鿡 �׸���
			virtual bool Release() override = 0;					// �ڿ� ����
			virtual void SetName(const std::wstring& _name)		// ��ü�� �̸�����
			{
				name = _name;
			}
			virtual const std::wstring& GetName()					// ��ü�� �̸�����
			{
				return name;
			}
		protected:
			std::wstring name;
		};

		class Core : public D3D , public IRenderable
		{
		private:
			Util::FPSCounter*	fpsCounter = nullptr;
		//	GumSky		*m_pGumSky;
		public:
			Core() noexcept;
			virtual ~Core();
		
			//��� Ŭ������ �ݵ�� �Ʒ��� �Լ��� �����Ѵ�.
			virtual bool	Init() override = 0;
			virtual bool	Frame() override = 0;
			virtual bool	Render() override = 0;
			virtual bool	Release() override = 0;
		
			__int64			Run();

			virtual bool	SetWin( const std::wstring& _titleName , unsigned int _width = 640 , unsigned int _height = 480 ) override;

		private:
			//�ʱ�ȭ
			bool	CoreInit();
			bool	PreCoreInit();
			bool	PostCoreInit();
			//���
			bool	CoreFrame();
			bool	PreCoreFrame();
			bool	PostCoreFrame();
			//��ο�
			bool	CoreRender();
			bool	PreCoreRender();
			bool	PostCoreRender();
			//����
			bool	CoreRelease();
			bool	PreCoreRelease();
			bool	PostCoreRelease();
		};
	}
}