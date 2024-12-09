#include "window.h"
#include "shaders.h"
#include "vertex.h"
#include "mesh.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	device d;
	//Plane p;
	//Cube c;
	//Sphere sp;
	//Tree t;
	Pine p;
	//Sampler samp;
	TextureManager mmm;

	shader s;
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	//c.init(d);
	//p.init(d);
	//sp.init(d, 19, 19, 2);
	/*samp.init(d);
	samp.bind(d);*/
	//t.init(d);
	p.init(d, mmm);

	s.create(d, "pvs.txt", "treePs.txt");

		while (true)
		{

			win.processMessages();
			d.clear();
			//s.apply(d);
			//p.draw(&s, d);
			Matrix m;
			m = m.scale(Vec3(0.01f, 0.01f, 0.01f));
			//m = m.translation(Vec3(0, 0, 0));

			p.updateW(m);
			p.draw(&s, d, mmm);
			/*m = m.translation(Vec3(0, 0, 0));
			c.updateW(m);
			c.draw(&s, d);
			m = m.translation(Vec3(5, 0, 0));
			c.updateW(m);
			c.draw(&s, d);*/
			//sp.draw(&s, d);
			d.present();
			
		}

}
