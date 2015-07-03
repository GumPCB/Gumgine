#include <iostream>
#include <Windows.h>
#include "../Gumgine/Singleton/Singleton.h"

class AAA
{
public:
	AAA() {};
	~AAA() {};
	virtual void print()
	{
		std::cout << L"AAA" << std::endl;
	}
};

class BBB : AAA
{
public:
	BBB() {};
	~BBB() {};
	virtual void print()
	{
		std::cout << L"BBB" << std::endl;
	}
};

class CCC : AAA
{
public:
	CCC() {};
	~CCC() {};
	virtual void print()
	{
		std::cout << L"CCC" << std::endl;
	}
};

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스

	//_CrtSetBreakAlloc( 338 );
	//auto &aaaFactory = Gumgine::Singleton::Manager< AAA >::GetInstance();
	auto &aaaFactory = Gumgine::Singleton::Factory< AAA >::GetInstance();
	aaaFactory.Register( L"BBB" , Gumgine::Singleton::CreateFunc< AAA , BBB > );

	//aaaFactory.Register( L"CCC" , []() -> AAA*
	//{
	//	return ( AAA* )new CCC;
	//} );

	//auto bbbbb = aaaFactory.Create( L"BBB" );
	//bbbbb->print();
	//SAFE_DEL( bbbbb );

	//bbbbb = aaaFactory.Create( L"CCC" );
	//bbbbb->print();
	//SAFE_DEL( bbbbb );

	//bbbbb = aaaFactory.Create( L"AAA" );
	////bbbbb->print();
	//SAFE_DEL( bbbbb );

	return 0;
}