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
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	d3dImmediateContext->ClearRenderTargetView( renderTargetView, blue );
	d3dImmediateContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH || D3D11_CLEAR_STENCIL, 1.0f, 0 );
	swapChain->Present( 0, 0 );
	return true;
}


bool DeviceSample::Release()
{
	return true;
}

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	const int maxThreadNum = 2;
	std::vector< std::thread > threadPool;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threadPool.push_back( std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			DeviceSample aaa;
			aaa.SetWin( threadName , 800 , 600 );
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