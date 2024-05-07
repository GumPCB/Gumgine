#include "DeviceSample.h"

int WINAPI wWinMain( HINSTANCE /*hInst*/ , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	//_CrtSetBreakAlloc( 319 );

	std::wstring threadName = L"Templete";
	std::wcout << threadName << L", pid = " << std::this_thread::get_id() << std::endl;
	DeviceSample aaa;
	aaa.SetWin(threadName, 800, 600);
	aaa.Run();

	return 0;
}