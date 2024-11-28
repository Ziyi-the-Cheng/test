#include "window.h"
#include "shaders.h"
#include "vertex.h"
#include "mesh.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	device d;
	shader s;
	plane p;

	
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	p.init(d);
	s.create(d, "nvs.txt", "nps.txt");
		while (true)
		{
			win.processMessages();
			d.clear();
			s.apply(d);
			p.geometry.draw(d);
			d.present();
			
		}

}
