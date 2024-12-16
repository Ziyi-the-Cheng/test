#pragma once
#include "ma.h"

class Camera {
public:
	Vec3 from;
	Vec3 to;
	Vec3 up;
	Matrix vp;
	float mouseXLastFrame;
	float mouseYLastFrame;
	float delta;

	Camera() {
		from = Vec3(0.f, 10.f, -10.f);
		to = Vec3(0.0f, 5.0f, 0.0f);
		up = Vec3(0.0f, 1.0f, 0.0f);
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 200.f, 0.1f);
		mouseXLastFrame = 0.f;
		mouseYLastFrame = 0.f;
	}
	
	void update(float x, float y, Matrix pw, float t) {
		delta = x - mouseXLastFrame;
		//lock the camera on T-Rex
		to = pw.mulPoint(Vec3(0.0f, 5.0f, 0.0f));
		from = pw.mulPoint(Vec3(0.f, 10.f, -10.f));

		from = vp.rotateY(10 * t * (delta)).mulVec(from - to) + to;
		
		vp = vp.lookAt(from, to, up) * vp.PerPro(1.f, 1.f, 20.f, 100.f, 0.1f);

		mouseXLastFrame = x;
		mouseYLastFrame = y;
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
	void moveBackward(bool collide) {
		if (!collide) {
			Vec3 d = to - from;
			d = d.normalize();
			/*from += d * 0.005;
			to += d * 0.005;*/

			from.z -= d.z * 0.01f;
			from.x -= d.x * 0.01f;
			to.z -= d.z * 0.01f;
			to.x -= d.x * 0.01f;
		}
	}
};