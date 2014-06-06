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

	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	const int maxThreadNum = 16;
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
	}
	threadPool.clear();

	return 0;
}