#pragma once
#include "window.h"
#include "shaders.h"
#include "vertex.h"
#include "mesh.h"
#include "Camera.h"
#include "GamesEngineeringBase.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	Window win;
	//create device
	device d;
	//create ground
	Plane p;
	//create camera
	Camera cam;

	//create game world objects
	Sky sky;
	loader rock;
	TRex tr;
	loader pine;
	loader pine1;
	loader pine2;

	//create texture managers, textures, collision cubes and light
	TextureManager mmm;
	TextureManager pmm;
	Texture skyt;
	collisionCube cc(Vec3(14.f, 0, 14.f), Vec3(16.f, 10, 16.f));
	collisionCube ccPine(Vec3(4.5f, 0, 4.5f), Vec3(5.5f, 10, 5.5f));
	collisionCube ccPine1(Vec3(4.5f, 0, -10.5f), Vec3(5.5f, 10, -9.5f));
	collisionCube ccPine2(Vec3(-5.5f, 0, 7.5f), Vec3(-4.5f, 10, 8.5f));
	lightSource li;

	//create shaders
	shader s;
	shader pp;
	shader spine;
	shader ssky;
	
	//initiate all components
	win.create(1024, 1024, "My Window");
	d.create(1024, 1024, win.hwnd, false);
	
	p.init(d);
	sky.init(d, 20, 20, 50);
	pine.init("pine.gem", d, pmm);
	pine1.init("pine.gem", d, pmm);
	pine2.init("pine.gem", d, pmm);
	rock.init("uc1jagbjw.gem", d, pmm);
	spine.create(d, "pvs.txt", "nmPS.txt");
	s.create(d, "TRexVS.txt", "treePs.txt");
	pp.create(d, "pvs.txt", "pps.txt");
	ssky.create(d, "pvs.txt", "treePs.txt");
	tr.init(d, "TRex.gem", mmm);
	skyt.load(&d, "sky.png");
	bool collide = false;

	GamesEngineeringBase::Timer tim;
		while (true)
		{
			bool moving = false;
			float dt = tim.dt();


			win.processMessages();
			d.clear();
			//update camera each frame
			cam.update(win.mousex, win.mousey, tr.planeWorld, dt);

			//movement control
			if (win.keyPressed('W')) {
				cam.moveForward(tr.collisioncube.isCollide(cc) || tr.collisioncube.isCollide(ccPine) || tr.collisioncube.isCollide(ccPine1) || tr.collisioncube.isCollide(ccPine2));
				tr.move(0.f, 1.f, cc, ccPine, ccPine1, ccPine2, dt);
				moving = true;
			}
			if (win.keyPressed('S')) {
				cam.moveBackward(tr.collisioncube.isCollide(cc) || tr.collisioncube.isCollide(ccPine) || tr.collisioncube.isCollide(ccPine1) || tr.collisioncube.isCollide(ccPine2));
				tr.move(0.f, -1.f, cc, ccPine, ccPine1, ccPine2, dt);
				moving = true;
			}

			tr.move(cam.delta, 0.f, cc, ccPine, ccPine1, ccPine2, dt);

			//draw everything
			sky.draw(&ssky, d, cam, skyt);
			p.draw(&pp, d, cam);
			Matrix m;
			m = m.scale(Vec3(0.5f, 0.5f, 0.5f)) * m.translation(Vec3(15.f, 0, 15.f));
			
			rock.updateW(m);
			rock.draw(&spine, d, pmm, cam, li);

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
			
			d.present();
			
		}

}
