#include <iostream>
#include <Windows.h>
#include "../Gumgine/Core/Window.h"

int WINAPI wWinMain( HINSTANCE hInst , HINSTANCE /*hPrevInstance*/ , LPWSTR /*lpCmdLine*/ , int /*nShowCmd*/ )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //검출 소스
	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	std::thread t1( [ = ]()
	{
		std::cout << "t1 : " << std::this_thread::get_id() << std::endl;
		Gumgine::Core::Window window;
		window.SetWin( hInst , L"t1" , 800 , 600 );
		window.Run();
	} );

	std::thread t2( [ = ]()
	{
		std::cout << "t2 : " << std::this_thread::get_id() << std::endl;
		Gumgine::Core::Window window;
		window.SetWin( hInst , L"t2" , 800 , 600 );
		window.Run();
	} );

	t1.join();
	t2.join();

	return 1;
}