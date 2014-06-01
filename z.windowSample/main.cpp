#include <iostream>
#include <Windows.h>
#include "../Gumgine/Core/Window.h"

int WINAPI wWinMain( HINSTANCE hInst , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //���� �ҽ�
	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	const int maxThreadNum = 8;
	std::vector< std::thread > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			Gumgine::Core::Window window;
			window.SetWin( hInst , threadName , 800 , 600 );
			window.Run();
		} ) );
	}

	for ( auto &thread : threadPool )
	{
		thread.join();
	}

	return 1;
}