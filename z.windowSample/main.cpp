#include <iostream>
#include <Windows.h>
#include "../Gumgine/Window.h"

INT WINAPI wWinMain( HINSTANCE hInst , HINSTANCE , LPWSTR , INT )
{
	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	std::thread t1( [ = ]()
	{
		std::cout << "t1 : " << std::this_thread::get_id() << std::endl;
		Gumgine::Window window;
		window.SetWindowSize( 800 , 600 );
		window.SetWin( hInst , L"t1" );
		window.Run();
	} );

	std::thread t2( [ = ]()
	{
		std::cout << "t2 : " << std::this_thread::get_id() << std::endl;
		Gumgine::Window window;
		window.SetWindowSize( 800 , 600 );
		window.SetWin( hInst , L"t2" );
		window.Run();
	} );

	t1.join();
	t2.join();

	return 1;
}