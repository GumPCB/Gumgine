#include <iostream>
#include <Windows.h>
#include "../Gumgine/Window.h"

INT WINAPI wWinMain( HINSTANCE hInst , HINSTANCE , LPWSTR , INT )
{
	std::mutex mutex;
	std::lock_guard< std::mutex > lock( mutex );

	Gumgine::Window window;
	Gumgine::Window window2;
	window.SetWindowSize( 800 , 600 );
	window.SetWin( hInst , L"Gum Box" );
	window2.SetWindowSize( 800 , 600 );
	window2.SetWin( hInst , L"Gum Box2" );
	window.Run();
	window2.Run();

	std::thread t1( [ &window ]() 
	{ 
		std::cout << "t1 : " << std::this_thread::get_id() << std::endl;
	} );

	std::thread t2( [ &window2 ]() 
	{ 
		std::cout << "t2 : " << std::this_thread::get_id() << std::endl;
	} );

	t1.join();
	Sleep( 10000 );
	t2.join();

	return 1;
}