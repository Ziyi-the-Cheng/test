#include "window.h"
#include "shaders.h"
#include "vertex.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	device d;
	Triangle tri;
	shader s;
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	tri.create(d);
	s.create(d, "vs.txt", "ps.txt");
		while (true)
		{
			win.processMessages();
			d.clear();
			s.apply(d);
			tri.draw(d);
			d.present();
			
		}

}
