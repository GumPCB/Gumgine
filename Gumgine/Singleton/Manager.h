#pragma once
#include "../GeStd.h"
//#include "Factory.h"

namespace Gumgine
{
	namespace Singleton
	{
		template< class T > class BasicSingleton;
		template< class T > class Factory;

		// 펙토리는 들고있고 싱글턴을 상속받고 펙토리의 인터페이스는 연결해주는 방식으로 만들자
		// 펙토리의 Create 함수 이름을 다른 것으로 바꾸자
		template< class T >
		class Manager : public BasicSingleton< Gumgine::Singleton::Manager< T > > , Gumgine::IRenderable
		{
		private:
			friend class BasicSingleton< Gumgine::Singleton::Manager< T > >;

		private:
			Manager() {};
			virtual ~Manager() {};

		public:
			void Register( const std::wstring& productName , std::function< T* ( ) > Func )
			{
				Gumgine::Singleton::Factory< T >::GetInstance().Register( productName , Func );
			}
			//virtual T* Make( const std::wstring& productName )
			//{
			//	return Gumgine::Singleton::Factory< T >::GetInstance().Create( productName );
			//}

			//무조건 추가
			unsigned int	Add( const std::wstring& name );
			//추가, 중복되면 이미 있는것의 인덱스를 리턴
			unsigned int	Create( const std::wstring& name );

			T*				GetPtr( const std::wstring& name );
			T*				GetPtr( unsigned int index );
			unsigned int	GetIndex( const std::wstring& name );
			unsigned int	GetIndex( T* child );

			unsigned int	GetLastIndex() const { return curIndex; }

			virtual bool	Init() override;	// 초기화
			virtual bool	Frame() override;	// 그리기 전에 할일
			virtual bool	Render() override;	// 화면에 그릴때
			virtual bool	Release() override;	// 자원 해제

		private:
			std::map< int , T* >	managedObject;
			unsigned int			curIndex = 0;
		};

		//template< typename Parent , typename Child , int N >
		//class GumTemplate
		//{
		//public:
		//	typedef	map <INT , Child*>						TemplateMap;
		//	typedef typename map <INT , Child*>::iterator	TemplateMapItor;
		//	TemplateMapItor									m_MapItor;
		//	TemplateMap										m_Map;
		//	DWORD											m_iCurIndex;
		//public:
		//	//무조건 추가
		//	DWORD	Add( const TCHAR* pName );
		//	//중복제거
		//	DWORD	Create( const TCHAR* pName );

		//	Child*	GetPtr( const TCHAR* pName );
		//	Child*	GetPtr( const DWORD& dwIndex );
		//	DWORD	GetIndex( const TCHAR* pName );
		//	DWORD	GetIndex( Child* pChild );

		//	DWORD	GetLastIndex() const { return m_iCurIndex; }

		//	bool	Init();
		//	bool	Frame();
		//	bool	Render();
		//	bool	Release();

		//	GumTemplate( void );
		//	~GumTemplate( void );
		//};

		//template< typename Parent , typename Child , int N >
		//Child* GumTemplate<Parent , Child , N>::GetPtr( const TCHAR* pName )
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		if ( pPoint->m_szName == pName )
		//		{
		//			return pPoint;
		//		}
		//	}

		//	return NULL;
		//}

		//template< typename Parent , typename Child , int N >
		//Child* GumTemplate<Parent , Child , N>::GetPtr( const DWORD& dwIndex )
		//{
		//	TemplateMapItor itor = m_Map.find( dwIndex );
		//	if ( itor == m_Map.end() ) return NULL;

		//	Child *pPoint;
		//	pPoint = ( Child * ) ( *itor ).second;
		//	return pPoint;
		//}

		//template< typename Parent , typename Child , int N >
		//DWORD GumTemplate<Parent , Child , N>::GetIndex( const TCHAR* pName )
		//{
		//	Child *pPoint;
		//	DWORD dwResult = 0;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		++dwResult;
		//		pPoint = ( Child * ) ( *itor ).second;
		//		if ( pPoint->m_szName == pName )
		//		{
		//			return dwResult;
		//		}
		//	}

		//	return 0;
		//}

		//template< typename Parent , typename Child , int N >
		//DWORD GumTemplate<Parent , Child , N>::GetIndex( Child* pChild )
		//{
		//	Child *pPoint;
		//	DWORD dwResult = 0;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		++dwResult;
		//		pPoint = ( Child * ) ( *itor ).second;
		//		if ( pPoint == pChild )
		//		{
		//			return dwResult;
		//		}
		//	}

		//	return 0;
		//}

		//template< typename Parent , typename Child , int N >
		//bool GumTemplate<Parent , Child , N>::Init()
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		pPoint->Init();
		//	}
		//	return true;
		//}

		//template< typename Parent , typename Child , int N >
		//bool GumTemplate<Parent , Child , N>::Frame()
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		pPoint->Frame();
		//	}
		//	return true;
		//}

		//template< typename Parent , typename Child , int N >
		//bool GumTemplate<Parent , Child , N>::Render()
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		pPoint->Render();
		//	}
		//	return true;
		//}

		//template< typename Parent , typename Child , int N >
		//bool GumTemplate<Parent , Child , N>::Release()
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		pPoint->Release();
		//	}
		//	return true;
		//}

		//template< typename Parent , typename Child , int N >
		//GumTemplate<Parent , Child , N>::GumTemplate( void )
		//{
		//	m_iCurIndex = 0;
		//	m_Map.clear();
		//}

		//template< typename Parent , typename Child , int N >
		//GumTemplate<Parent , Child , N>::~GumTemplate( void )
		//{
		//	Child *pPoint;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		pPoint = ( Child * ) ( *itor ).second;
		//		pPoint->Release();
		//		SAFE_DEL( pPoint );
		//	}
		//	m_Map.clear();
		//	m_iCurIndex = 0;
		//}

		////무조건 추가
		//template< typename Parent , typename Child , int N >
		//DWORD GumTemplate<Parent , Child , N>::Add( const TCHAR* pName )
		//{
		//	Child* pPoint = NULL;
		//	SAFE_NEW( pPoint , Child );
		//	pPoint->Init();
		//	pPoint->m_szName = pName;
		//	m_Map.insert( make_pair( ++m_iCurIndex , pPoint ) );

		//	return m_iCurIndex;
		//}
		////중복제거
		//template< typename Parent , typename Child , int N >
		//DWORD GumTemplate<Parent , Child , N>::Create( const TCHAR* pName )
		//{
		//	Child *pPoint;
		//	DWORD dwResult = 0;
		//	for ( TemplateMapItor itor = m_Map.begin(); itor != m_Map.end(); ++itor )
		//	{
		//		++dwResult;
		//		pPoint = ( Child * ) ( *itor ).second;
		//		if ( pPoint->m_szName == pName )
		//		{
		//			return dwResult;
		//		}
		//	}

		//	return Add( pName );
		//}
	}
}