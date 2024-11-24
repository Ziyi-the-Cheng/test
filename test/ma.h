#include <cmath>
#include <iostream>
#pragma once

#define max(a, b)(a > b ? a:b)
#define min(a, b)(a < b ? a:b)
class Vec3
{
public:
	Vec3() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
	Vec3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	union {
		float v[3];
		struct { float x, y, z; };
	};
	Vec3 operator+(const Vec3& pVec) const { return Vec3(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]); }
	Vec3& operator+=(const Vec3& pVec) { v[0] += pVec.v[0]; v[1] += pVec.v[1]; v[2] += pVec.v[2]; return *this; }
	Vec3 operator-(const Vec3& pVec) const { return Vec3(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]); }
	Vec3& operator-=(const Vec3& pVec) { v[0] -= pVec.v[0]; v[1] -= pVec.v[1]; v[2] -= pVec.v[2]; return *this; }
	Vec3 operator*(const Vec3& pVec) const { return Vec3(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]); }
	Vec3 operator*(const float val) const { return Vec3(v[0] * val, v[1] * val, v[2] * val); }
	Vec3& operator*=(const Vec3& pVec) { v[0] *= pVec.v[0]; v[1] *= pVec.v[1]; v[2] *= pVec.v[2]; return *this; }
	Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
	Vec3 operator/(const float val) const { return Vec3(v[0] / val, v[1] / val, v[2] / val); }
	float lenghSquar() { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	float length() { return sqrt(lenghSquar()); }
	Vec3 normalize(void) { float len = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); return Vec3(x * len, y * len, z * len); }

	float normalize_GetLength()
	{
		float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		float len = 1.0f / length;
		v[0] *= len; v[1] *= len; v[2] *= len;
		return length;
	}
	float Dot(const Vec3& pVec) const
	{
		return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2];
	}
	float Dot(const Vec3& v1, const Vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	Vec3 Cross(const Vec3& v1)
	{
		return Vec3(v1.v[1] * v[2] - v1.v[2] * v[1],
			v1.v[2] * v[0] - v1.v[0] * v[2],
			v1.v[0] * v[1] - v1.v[1] * v[0]);
	}
	Vec3 Max(const Vec3& v1, const Vec3& v2)
	{
		return Vec3(max(v1.v[0], v2.v[0]),
			max(v1.v[1], v2.v[1]),
			max(v1.v[2], v2.v[2]));
	}
	float Max() const
	{
		return max(x, max(y, z));
	}
	Vec3 Min(const Vec3& v1, const Vec3& v2)
	{
		return Vec3(min(v1.v[0], v2.v[0]),
			min(v1.v[1], v2.v[1]),
			min(v1.v[2], v2.v[2]));
	}
	float Min() const
	{
		return min(x, min(y, z));
	}
	float distanceTo(Vec3& v) {
		float a = x - v.x;
		float b = y - v.y;
		float c = z - v.z;
		return sqrtf(a * a + b * b + c * c);
	}
	void display() {
		std::cout << x << "\t" << y << "\t" << z << "\n";
	}
};


class Colour {
public:
	union {
		struct {
			float r;
			float g;
			float b;
		};
		float c[3];
	};
	Colour() {
		r = 0.f;
		g = 0.f;
		b = 0.f;
	}
	Colour(float _r, float _g, float _b) {
		r = _r;
		g = _g;
		b = _b;
	}
	/*Colour(unsigned char _r, unsigned char _g, unsigned char _b) {
		r = _r / 255.f;
		g = _g / 255.f;
		b = _b / 255.f;
	}*/
	Colour operator+(const Colour& colour) const { return Colour(r + colour.r, g + colour.g, b + colour.b); }
	Colour operator*(const Colour& colour) const { return Colour(r * colour.r, g * colour.g, b * colour.b); }
	Colour operator*(const float p) const { return Colour(r * p, g * p, b * p); }
	Colour operator/(const float p) const { return Colour(r / p, g / p, b / p); }
};
