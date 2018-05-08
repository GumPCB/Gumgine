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
	static auto backBufferColor = DirectX::Colors::LightSteelBlue;
	backBufferColor.f[ 0 ] += 0.001f;
	if ( backBufferColor.f[ 0 ] > 1.0f )
	{
		backBufferColor.f[ 0 ] -= 1.0f;
	}
	backBufferColor.f[ 1 ] -= 0.001f;
	if ( backBufferColor.f[ 1 ] < 0.0f )
	{
		backBufferColor.f[ 1 ] += 1.0f;
	}

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
	return true;
}

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	const int maxThreadNum = 1;
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