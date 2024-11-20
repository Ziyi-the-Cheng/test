#include "window.h"
#include "device.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	device d;
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
		while (true)
		{
			win.processMessages();

			
		}

}
