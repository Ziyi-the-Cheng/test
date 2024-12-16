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
	Sky sky;
	//Cube c;
	//Sphere sp;
	//Tree t;
	loader lol;
	TRex tr;
	loader pine;
	loader pine1;
	loader pine2;
	//Sampler samp;
	TextureManager mmm;
	TextureManager pmm;
	Texture skyt;
	collisionCube cc(Vec3(14.f, 0, 14.f), Vec3(16.f, 10, 16.f));
	collisionCube ccPine(Vec3(4.5f, 0, 4.5f), Vec3(5.5f, 10, 5.5f));
	collisionCube ccPine1(Vec3(4.5f, 0, -10.5f), Vec3(5.5f, 10, -9.5f));
	collisionCube ccPine2(Vec3(-5.5f, 0, 7.5f), Vec3(-4.5f, 10, 8.5f));


	lightSource li;

	shader s;
	shader pp;
	shader spine;
	shader ssky;
	
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	//c.init(d);
	p.init(d);
	sky.init(d, 20, 20, 50);
	//sp.init(d, 19, 19, 2);
	/*samp.init(d);
	samp.bind(d);*/
	//t.init(d);
	pine.init("pine.gem", d, pmm);
	pine1.init("pine.gem", d, pmm);
	pine2.init("pine.gem", d, pmm);

	lol.init("uc1jagbjw.gem", d, pmm);
	spine.create(d, "pvs.txt", "nmPS.txt");
	s.create(d, "TRexVS.txt", "treePs.txt");
	pp.create(d, "pvs.txt", "pps.txt");
	ssky.create(d, "pvs.txt", "treePs.txt");
	tr.init(d, "TRex.gem", mmm);
	skyt.load(&d, "sky.png");
	bool collide = false;
	
		while (true)
		{
			bool moving = false;

			win.processMessages();
			d.clear();
			//s.apply(d);

			cam.update(win.mousex, win.mousey, tr.planeWorld);

			collide = tr.collisioncube.isCollide(cc) || tr.collisioncube.isCollide(ccPine) || tr.collisioncube.isCollide(ccPine1) || tr.collisioncube.isCollide(ccPine2);

			if (win.keyPressed('W')) {
				cam.moveForward(tr.collisioncube.isCollide(cc) || tr.collisioncube.isCollide(ccPine) || tr.collisioncube.isCollide(ccPine1) || tr.collisioncube.isCollide(ccPine2));
				tr.move(0.f, 1.f, cc, ccPine, ccPine1, ccPine2);
				moving = true;
			}
			if (win.keyPressed('S')) {
				cam.moveBackward(tr.collisioncube.isCollide(cc) || tr.collisioncube.isCollide(ccPine) || tr.collisioncube.isCollide(ccPine1) || tr.collisioncube.isCollide(ccPine2));
				tr.move(0.f, -1.f, cc, ccPine, ccPine1, ccPine2);
				moving = true;
			}

			tr.move(cam.delta, 0.f, cc, ccPine, ccPine1, ccPine2);


			sky.draw(&ssky, d, cam, skyt);
			p.draw(&pp, d, cam);
			Matrix m;
			m = m.scale(Vec3(0.5f, 0.5f, 0.5f)) * m.translation(Vec3(15.f, 0, 15.f));
			
			lol.updateW(m);
			lol.draw(&spine, d, pmm, cam, li);

			m = m.scale(Vec3(0.01f, 0.01f, 0.01f)) * m.translation(Vec3(5.f, 0, 5.f));
			pine.updateW(m);
			pine.draw(&spine, d, pmm, cam, li);
			m = m.scale(Vec3(0.01f, 0.01f, 0.01f)) * m.translation(Vec3(5.f, 0, -10.f));
			pine1.updateW(m);
			pine1.draw(&spine, d, pmm, cam, li);
			m = m.scale(Vec3(0.01f, 0.01f, 0.01f)) * m.translation(Vec3(-5.f, 0, 8.f));
			pine2.updateW(m);
			pine2.draw(&spine, d, pmm, cam, li);
			tr.draw(&s, d, mmm, cam, moving);
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
