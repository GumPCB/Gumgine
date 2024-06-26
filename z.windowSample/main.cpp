#include "GeStd.h"

void testThread2()
{
	const int maxThreadNum = 4096;
	std::vector< std::thread* > threads;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threads.push_back( new std::thread( [ = ]()
		{
			Gumgine::Core::Window window;
		} ) );
	}

	for ( auto &thread : threads )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threads );
	threads.clear();
}

void testThread()
{
	const int maxThreadNum = 8;
	std::vector< std::thread* > threads;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threads.push_back( new std::thread( [ = ]()
		{
			testThread2();
		} ) );
	}

	for ( auto &thread : threads )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threads );
	threads.clear();
}

void MakeWindow()
{
	const int maxThreadNum = 4;
	std::vector< std::thread* > threads;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threads.push_back( new std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			Gumgine::Core::Window window;
			//window.SetWin( threadName , 800 , 600 );
			//window.Run();
		} ) );
	}

	for ( auto &thread : threads )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threads );
	threads.clear();
}

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //���� �ҽ�
	//_CrtSetBreakAlloc( 338 );
	//std::wstring num;
	//__int64 aa = -10000000000000000;
	//num = Gumgine::Util::Converter::ToWString( aa );

	//MakeWindow();
	testThread();

	return 0;
}