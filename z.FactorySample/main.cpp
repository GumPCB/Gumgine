#include <iostream>
#include <Windows.h>
#include "../Gumgine/Singleton/Singleton.h"

class AAA : public Gumgine::IManagedRenderable
{
public:
	AAA() {};
	~AAA() {};
	virtual void print()
	{
		std::cout << L"AAA" << std::endl;
	}
	virtual bool Init() override						// �ʱ�ȭ
	{
		return true;
	}
	virtual bool Frame() override						// �׸��� ���� ����
	{
		return true;
	}
	virtual bool Render() override						// ȭ�鿡 �׸���
	{
		return true;
	}
	virtual bool Release() override					// �ڿ� ����
	{
		return true;
	}
};

class BBB : public AAA
{
public:
	BBB() {};
	~BBB() {};
	virtual void print()
	{
		std::cout << L"BBB" << std::endl;
	}
};

class CCC : public AAA
{
public:
	CCC() {};
	~CCC() {};
	virtual void print()
	{
		std::cout << L"CCC" << std::endl;
	}
};

class DDD : public Gumgine::IManagedRenderable
{
public:
	DDD() {};
	~DDD() {};
	virtual void print()
	{
		std::cout << L"DDD" << std::endl;
	}
	virtual bool Init() override						// �ʱ�ȭ
	{
		return true;
	}
	virtual bool Frame() override						// �׸��� ���� ����
	{
		return true;
	}
	virtual bool Render() override						// ȭ�鿡 �׸���
	{
		return true;
	}
	virtual bool Release() override					// �ڿ� ����
	{
		return true;
	}
};

class AAAManager : public Gumgine::Singleton::Manager< AAA >
{
private:
	friend class Gumgine::Singleton::Manager< AAA >;
private:
	virtual ~AAAManager() {};
};

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //���� �ҽ�

	//_CrtSetBreakAlloc( 338 );
	auto &aaaFactory = AAAManager::GetInstance();
	//auto &aaaFactory = Gumgine::Singleton::Factory< AAA >::GetInstance();
	aaaFactory.RegisterType( L"AAA" , Gumgine::Singleton::CreateSharedPtrFunc< AAA > );
	aaaFactory.RegisterType( L"BBB" , Gumgine::Singleton::CreateSharedPtrFunc< BBB > );
	aaaFactory.RegisterType( L"CCC" , Gumgine::Singleton::CreateSharedPtrFunc< CCC > );
	//aaaFactory.RegisterType( L"DDD" , Gumgine::Singleton::CreateSharedPtrFunc< DDD > ); // �翬�� �̰� �ȵ�

	//aaaFactory.RegisterType( L"CCC" , []() -> AAA*
	//{
	//	return ( AAA* )new CCC;
	//} );

	auto index = aaaFactory.Create( L"b1", L"BBB" );
	auto bbbbb = aaaFactory.GetPtr( index );
	bbbbb->print();
	//SAFE_DEL( bbbbb );

	index = aaaFactory.Create( L"c1", L"CCC" );
	bbbbb = aaaFactory.GetPtr( index );
	bbbbb->print();
	//SAFE_DEL( bbbbb );

	index = aaaFactory.Create( L"a1", L"AAA" );
	bbbbb = aaaFactory.GetPtr( index );
	bbbbb->print();
	//bbbbb->print();
	//SAFE_DEL( bbbbb );

	return 0;
}