#pragma once
#include "ma.h"

class lightSource {
public:
	Vec3 position;
	Colour color;

	lightSource() {
		position = Vec3(0, 30, 0);
		color = Colour(1.f, 1.f, 1.f);
	}

};