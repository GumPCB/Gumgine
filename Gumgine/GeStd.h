#pragma once
#include <Windows.h>
//#include <stdlib.h>
//#include <atlconv.h>
#include <tchar.h>
//#include <d3d9.h>
//#include <d3dx9.h>
#include <xinput.h>

#include <thread>
#include <mutex>
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

//using namespace std;

#define SAFE_ZERO( A )					{ A = 0; }
#define SAFE_NEW( A , B )				{ if( !A ) A = new B; }
#define SAFE_DEL( A )					{ if( A ) delete A; ( A ) = nullptr; }	std::unique_ptr
#define SAFE_ARRAY_NEW( A , B , C )		{ if( !A && C ) A = new B[C]; }
#define SAFE_ARRAY_DEL( A )				{ if( A ) delete [] A; ( A ) = nullptr; }
#define SAFE_RELEASE( A )				{ if( A ) { ( A )->Release(); ( A ) = nullptr; } }
#define NEW_CLEAR( A , B )				{ if( !A ) A = new B(); if( A ) memset( A, 0, sizeof( B ) ); }
#define NEW_ARRAY_CLEAR( A , B , C )	{ if( !A && C ) A = new B[ C ]; if( A ) memset( A, 0, sizeof( B ) * C ); }
#define SAFE_STL_CONTAINER_DELETE( A )	{ for ( auto iter = A.begin() ; iter != A.end() ; ++iter ) SAFE_DEL( *iter ); }
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
	template< class T > class GeSingleton
	{
	public:
		static T& GetInstance()
		{
			static T theSingleInstance;
			return theSingleInstance;
		}
	};

	class GumCore
	{
		virtual bool Init() = 0;	// 초기화
		virtual bool Frame() = 0;	// 그리기 전에 할일
		virtual bool Render() = 0;	// 화면에 그릴때
		virtual bool Release() = 0; // 자원 해제
	};
}