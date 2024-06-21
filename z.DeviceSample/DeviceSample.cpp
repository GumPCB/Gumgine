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

	//backBufferColor.f[ 0 ] += static_cast< float >( timer.GetDeltaTime() );
	//if ( backBufferColor.f[ 0 ] > 1.0f )
	//{
	//	backBufferColor.f[ 0 ] -= 1.0f;
	//}
	//backBufferColor.f[ 1 ] -= dist( randomdevice );
	//if ( backBufferColor.f[ 1 ] < 0.0f )
	//{
	//	backBufferColor.f[ 1 ] += 1.0f;
	//}
	//backBufferColor.f[2] += dist(randomdevice);
	//if (backBufferColor.f[2] > 1.0f)
	//{
	//	backBufferColor.f[2] -= 1.0f;
	//}
	return true;
}

bool DeviceSample::Render()
{
	Gumgine::Core::Vertex1 vertices[] =
	{
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::White) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Black) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Red) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Green) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Blue) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Yellow) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Cyan) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Magenta) }
	};

	const UINT64 vbByteSize = 8 * sizeof(Gumgine::Core::Vertex1);

	Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
	VertexBufferGPU = d3dUtil::CreateDefaultBuffer(d3dDevice.Get(), commandList.Get(), vertices, vbByteSize, VertexBufferUploader);
	
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
	vbv.StrideInBytes = sizeof(Gumgine::Core::Vertex1);
	vbv.SizeInBytes = 8 * sizeof(Gumgine::Core::Vertex1);

	D3D12_VERTEX_BUFFER_VIEW vertexBuffers[1] = { vbv };
	commandList->IASetVertexBuffers(0, 1, vertexBuffers);

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