#include <Windows.h>
#include "../Gumgine/Window.h"

INT WINAPI wWinMain( HINSTANCE hInst , HINSTANCE , LPWSTR , INT )
{
	Gumgine::Window window;
	window.SetWindowSize( 800 , 600 );
	window.SetWin( hInst , L"Gum Box" );
	window.Run();
	return 1;
}