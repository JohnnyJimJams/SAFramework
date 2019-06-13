#include <Windows.h>
#include "winuser.h"
#include "DemoPlayer.h"

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	DemoPlayer* demoPlayer = new DemoPlayer(desktopWidth, desktopHeight);
	demoPlayer->Start();
	
	delete demoPlayer;
	return 0;
}
