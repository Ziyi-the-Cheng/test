#pragma once
#include "window.h"
#include "shaders.h"
#include "vertex.h"
#include "mesh.h"
#include "Camera.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;

	/*int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	win.create(screenWidth, screenHeight, "My Window");
	SetWindowLong(win.hwnd, GWL_STYLE, WS_POPUP);
	SetWindowPos(win.hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED | SWP_SHOWWINDOW);*/

	device d;
	Plane p;
	Camera cam;
	Sky sky;
	//Cube c;
	//Sphere sp;
	//Tree t;
	loader lol;
	TRex tr;
	//Sampler samp;
	TextureManager mmm;
	TextureManager pmm;
	Texture skyt;
	

	shader s;
	shader pp;
	shader spine;
	shader ssky;
	
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	//c.init(d);
	p.init(d);
	sky.init(d, 20, 20, 80);
	//sp.init(d, 19, 19, 2);
	/*samp.init(d);
	samp.bind(d);*/
	//t.init(d);
	lol.init("rlctbdhqx.gem", d, pmm);
	spine.create(d, "pvs.txt", "treePs.txt");
	s.create(d, "TRexVS.txt", "treePs.txt");
	pp.create(d, "pvs.txt", "pps.txt");
	ssky.create(d, "pvs.txt", "treePs.txt");
	tr.init(d, "TRex.gem", mmm);
	skyt.load(&d, "sky.png");
	
		while (true)
		{

			win.processMessages();
			d.clear();
			//s.apply(d);

			cam.update(win.mousex, win.mousey);


			if (win.keyPressed('D')) cam.moveRight();
			if (win.keyPressed('A')) cam.moveLeft();
			if (win.keyPressed('W')) {
				cam.moveForward();
				tr.moveRight(0.f, 1.f);
			}
			if (win.keyPressed('S')) cam.moveBackward();
			if (win.keyPressed(' ')) cam.moveUp();
			if (win.keyPressed('C')) cam.moveDown();
			

			tr.moveRight(cam.delta, 0.f);




			sky.draw(&ssky, d, cam, skyt);
			p.draw(&pp, d, cam);
			Matrix m;
			m = m.scale(Vec3(0.1f, 0.1f, 0.1f)) * m.translation(Vec3(0, 0, 5.f));
		
			lol.updateW(m);
			lol.draw(&spine, d, pmm, cam);
			tr.draw(&s, d, mmm, cam);
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
