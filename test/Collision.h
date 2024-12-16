#pragma once
#include "ma.h"

class collisionCube {
public:
	Vec3 min;
	Vec3 max;

	collisionCube(Vec3 _min, Vec3 _max) {
		min = _min;
		max = _max;
	}
	collisionCube(){}

	bool isCollide(collisionCube cc) {
		return ((min.x <= cc.max.x && max.x >= cc.min.x) && (min.y <= cc.max.y && max.y >= cc.min.y) && (min.z <= cc.max.z && max.z >= cc.min.z));
	}

	void update(Vec3 move) {
		min += move;
		max += move;
	}

};