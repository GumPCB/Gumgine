#include "DeviceSample.h"

DeviceSample::DeviceSample()
	: dist( 0.0f, 0.001f )
{}


DeviceSample::~DeviceSample()
{}

bool DeviceSample::Init()
{
	timer.Init();
	return true;
}


bool DeviceSample::Frame()
{
	timer.Frame();

	backBufferColor.f[ 0 ] += static_cast< float >( timer.GetDeltaTime() );
	if ( backBufferColor.f[ 0 ] > 1.0f )
	{
		backBufferColor.f[ 0 ] -= 1.0f;
	}
	backBufferColor.f[ 1 ] -= dist( randomdevice );
	if ( backBufferColor.f[ 1 ] < 0.0f )
	{
		backBufferColor.f[ 1 ] += 1.0f;
	}
	return true;
}

bool DeviceSample::Render()
{
	ThrowIfFailed( commandAllocator->Reset() );
	ThrowIfFailed( commandList->Reset( commandAllocator.Get(), nullptr ) );

	auto currentBackBufferView = CurrentBackBufferView();
	auto depthStencilView = DepthStencilView();
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition( CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET );
	commandList->ResourceBarrier( 1, &barrier );
	commandList->RSSetViewports( 1, &viewPort );
	commandList->RSSetScissorRects( 1, &scissorRect );
	commandList->ClearRenderTargetView( currentBackBufferView, backBufferColor, 0, nullptr );
	commandList->ClearDepthStencilView( depthStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr );
	commandList->OMSetRenderTargets( 1, &currentBackBufferView, true, &depthStencilView );
	barrier = CD3DX12_RESOURCE_BARRIER::Transition( CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT );
	commandList->ResourceBarrier( 1, &barrier );
	ThrowIfFailed( commandList->Close() );
	ID3D12CommandList* commandLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists( _countof( commandLists ), commandLists );
	ThrowIfFailed( swapChain->Present( 0, 0 ) );
	currentBackBuffer = ( currentBackBuffer + 1 ) % swapChainBufferCount;
	FlushCommandQueue();
	return true;
}


bool DeviceSample::Release()
{
	timer.Release();
	return true;
}

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	const int maxThreadNum = 1;
	std::vector< std::thread > threads;
	for ( int i = 1; i <= maxThreadNum; ++i )
	{
		threads.push_back( std::thread( [ = ]()
		{
			std::wstring threadName = L"T" + std::to_wstring( i );
			std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
			DeviceSample aaa;
			aaa.SetWin( threadName , 800 , 600 );
			aaa.Run();
		} ) );
	}

	for ( auto &thread : threads )
	{
		thread.join();
	}
	threads.clear();

	return 0;
}