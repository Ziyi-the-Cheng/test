#pragma once
#include "ma.h"

class Camera {
public:
	Vec3 from;
	Vec3 to;
	Vec3 up;
	Vec3 forward;
	Matrix planeWorld;
	Matrix vp;
	float t;
	float mouseXLastFrame;
	float mouseYLastFrame;
	float delta;

	Camera() {
		from = Vec3(0.f, 10.f, -10.f);
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
	void update(float x, float y, Matrix pw) {
		delta = x - mouseXLastFrame;

		to = pw.mulPoint(Vec3(0.0f, 5.0f, 0.0f));
		from = pw.mulPoint(Vec3(0.f, 10.f, -10.f));

		from = vp.rotateY(0.01f * (delta)).mulVec(from - to) + to;
		//to = vp.rotateY(0.01f * (delta)).mulVec(to - from) + from;

		//to = vp.rotateZ(0.01f * (y - mouseYLastFrame)).mulVec(to - from) + from;
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);

		mouseXLastFrame = x;
		mouseYLastFrame = y;
	}
	void moveRight() {
		Vec3 d = to - from;
		d = vp.rotateY(3.14159265f / 2.f).mulVec(d);
		d = d.normalize();
		/*from += d * 0.005;
		to += d * 0.005;*/

		from.z += d.z * 0.01f;
		from.x += d.x * 0.01f;
		to.z += d.z * 0.01f;
		to.x += d.x * 0.01f;
	}
	void moveLeft() {
		Vec3 d = to - from;
		d = vp.rotateY(3.14159265f * 3 / 2.f).mulVec(d);
		d = d.normalize();
		from += d * 0.005;
		to += d * 0.005;
	}
	void moveForward(bool collide) {
		if (!collide) {
			Vec3 d = to - from;
			d = d.normalize();
			/*from += d * 0.005;
			to += d * 0.005;*/

			from.z += d.z * 0.01f;
			from.x += d.x * 0.01f;
			to.z += d.z * 0.01f;
			to.x += d.x * 0.01f;
		}
	}
	void moveBackward() {
		Vec3 d = to - from;
		d = d.normalize();
		from -= d * 0.005;
		to -= d * 0.005;
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