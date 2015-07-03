#include <iostream>
#include <Windows.h>
#include "../Gumgine/Core/Window.h"
#include "../Gumgine/Util/Converter.h"

void testThread2()
{
	const int maxThreadNum = 4096;
	std::vector< std::thread* > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( new std::thread( [ = ]()
		{
			Gumgine::Core::Window window;
		} ) );
	}

	for ( auto &thread : threadPool )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threadPool );
	threadPool.clear();
}

void testThread()
{
	const int maxThreadNum = 8;
	std::vector< std::thread* > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( new std::thread( [ = ]()
		{
			testThread2();
		} ) );
	}

	for ( auto &thread : threadPool )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threadPool );
	threadPool.clear();
}

void MakeWindow()
{
	const int maxThreadNum = 4;
	std::vector< std::thread* > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( new std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			Gumgine::Core::Window window;
			//window.SetWin( threadName , 800 , 600 );
			//window.Run();
		} ) );
	}

	for ( auto &thread : threadPool )
	{
		thread->join();
	}

	SAFE_STL_CONTAINER_DELETE( threadPool );
	threadPool.clear();
}

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 338 );
	//std::wstring num;
	//__int64 aa = -10000000000000000;
	//num = Gumgine::Util::Converter::ToWString( aa );
	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	//MakeWindow();
	testThread();

	return 0;
}