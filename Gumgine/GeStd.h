#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>
#include <memory>
#include <cassert>
#include <exception>
#include <chrono>

#include <Windows.h>
#include <xinput.h>
#include <D3D12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <comdef.h>

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
	class IRenderable
	{
	public:
		virtual bool Init() = 0;	// 초기화
		virtual bool Frame() = 0;	// 그리기 전에 할일
		virtual bool Render() = 0;	// 화면에 그릴때
		virtual bool Release() = 0; // 자원 해제
	};

	class IManagedRenderable : IRenderable
	{
	public:
		virtual bool Init() override = 0;						// 초기화
		virtual bool Frame() override = 0;						// 그리기 전에 할일
		virtual bool Render() override = 0;						// 화면에 그릴때
		virtual bool Release() override = 0;					// 자원 해제
		virtual void SetName( const std::wstring& _name )		// 객체의 이름설정
		{
			name = _name;
		}
		virtual const std::wstring& GetName()					// 객체의 이름리턴
		{
			return name;
		}
	protected:
		std::wstring name;
	};
}