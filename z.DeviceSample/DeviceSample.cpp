#include <iostream>
#include "DeviceSample.h"


DeviceSample::DeviceSample()
{}


DeviceSample::~DeviceSample()
{}

bool DeviceSample::Init()
{
	return true;
}


bool DeviceSample::Frame()
{
	return true;
}

bool DeviceSample::Render()
{
	return true;
}


bool DeviceSample::Release()
{
	return true;
}

int WINAPI wWinMain( HINSTANCE hInst , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	const int maxThreadNum = 1;
	std::vector< std::thread > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			DeviceSample aaa;
			aaa.SetWin( hInst , threadName , 800 , 600 );
			aaa.Run();
		} ) );
	}

	for ( auto &thread : threadPool )
	{
		thread.join();
		thread.~thread();
	}
	threadPool.clear();

	return 1;
}