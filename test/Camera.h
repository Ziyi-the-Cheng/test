#pragma once
#include "ma.h"

class Camera {
public:
	Vec3 from;
	Vec3 to;
	Vec3 up;
	Matrix planeWorld;
	Matrix vp;
	float t;
	float mouseXLastFrame;
	float mouseYLastFrame;

	Camera() {
		from = Vec3(10.f, 5.f, 0.f);
		to = Vec3(0.0f, 5.0f, 0.0f);
		up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
		t = 0.f;
		mouseXLastFrame = 0.f;
		mouseYLastFrame = 0.f;
	}
	void updateW(Matrix input) {
		planeWorld = input;
	}
	void update(float x, float y) {
		float distance = from.distanceTo(to);
		float h = (x / 1024.f) * 6.283f;
		float v = (y / 1024.f) * 6.283f;
		to.z = -distance * sin(h);
		to.x = distance * cos(h);

		/*to.y = distance * sin(v);
		to.x = distance * cos(v);*/
		//to.y = -0.005 * y;
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);
	}
	void moveRight() {
		from.z += 0.005;
		to.z += 0.005;
	}
	void moveLeft() {
		from.z -= 0.005;
		to.z -= 0.005;
	}
	void moveForward() {
		Vec3 d = to - from;
		d = d.normalize();
		from.x += 0.005 * d.x;
		from.y += 0.005 * d.y;
		from.z += 0.005 * d.z;

		to.x += 0.005 * d.x;
		to.y += 0.005 * d.y;
		to.z += 0.005 * d.z;
	}
	void moveBackward() {
		Vec3 d = to - from;
		d = d.normalize();
		from.x -= 0.005 * d.x;
		from.y -= 0.005 * d.y;
		from.z -= 0.005 * d.z;

		to.x -= 0.005 * d.x;
		to.y -= 0.005 * d.y;
		to.z -= 0.005 * d.z;
	}
	void moveUp() {
		from.y += 0.005;
		to.y += 0.005;
	}
	void moveDown() {
		from.y -= 0.005;
		to.y -= 0.005;
	}
};