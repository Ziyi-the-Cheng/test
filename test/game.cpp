#pragma once
#include "window.h"
#include "shaders.h"
#include "vertex.h"
#include "mesh.h"
#include "Camera.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	device d;
	Plane p;
	Camera cam;
	//Cube c;
	//Sphere sp;
	//Tree t;
	Pine pine;
	TRex tr;
	//Sampler samp;
	TextureManager mmm;
	TextureManager pmm;

	shader s;
	shader pp;
	shader spine;
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	//c.init(d);
	p.init(d);
	//sp.init(d, 19, 19, 2);
	/*samp.init(d);
	samp.bind(d);*/
	//t.init(d);
	pine.init(d, pmm);
	spine.create(d, "pvs.txt", "treePs.txt");
	s.create(d, "TRexVS.txt", "treePs.txt");
	pp.create(d, "pvs.txt", "pps.txt");
	tr.init(d, "TRex.gem", mmm);
	
		while (true)
		{

			win.processMessages();
			d.clear();
			//s.apply(d);
			if (win.keyPressed('D')) cam.moveRight();
			if (win.keyPressed('A')) cam.moveLeft();
			if (win.keyPressed('W')) cam.moveForward();
			if (win.keyPressed('S')) cam.moveBackward();
			if (win.keyPressed(' ')) cam.moveUp();
			if (win.keyPressed('C')) cam.moveDown();


			cam.update(win.mousex, win.mousey);
			p.draw(&pp, d, cam);
			Matrix m;
			m = m.translation(Vec3(0.01f, 0.01f, 0.01f));

			pine.updateW(m);
			pine.draw(&spine, d, pmm);
			//tr.draw(&s, d, mmm, cam);
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
