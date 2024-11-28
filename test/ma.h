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

class Vec4
{
public:
	Vec4() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}
	Vec4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	union {
		float v[4];
		struct { float x, y, z, w; };
	};
	Vec4 operator+(const Vec4& pVec) const { return Vec4(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2], v[3] + pVec.v[3]); }
	Vec4& operator+=(const Vec4& pVec) { v[0] += pVec.v[0]; v[1] += pVec.v[1]; v[2] += pVec.v[2]; v[3] += pVec.v[3]; return *this; }
	Vec4 operator-(const Vec4& pVec) const { return Vec4(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2], v[3] - pVec.v[3]); }
	Vec4& operator-=(const Vec4& pVec) { v[0] -= pVec.v[0]; v[1] -= pVec.v[1]; v[2] -= pVec.v[2]; v[3] -= pVec.v[3]; return *this; }
	Vec4 operator*(const Vec4& pVec) const { return Vec4(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2], v[3] * pVec.v[3]); }
	Vec4 operator*(const float val) const { return Vec4(v[0] * val, v[1] * val, v[2] * val, v[3] * val); }
	Vec4& operator*=(const Vec4& pVec) { v[0] *= pVec.v[0]; v[1] *= pVec.v[1]; v[2] *= pVec.v[2], v[3] *= pVec.v[3]; return *this; }
	Vec4 operator-() const { return Vec4(-v[0], -v[1], -v[2], -v[3]); }
	Vec4 operator/(const float val) const { return Vec4(v[0] / val, v[1] / val, v[2] / val, v[3] / val); }
	float lenghSquar() { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]; }
	float length() { return sqrt(lenghSquar()); }
	Vec4 normalize(void) { float len = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]); return Vec4(x * len, y * len, z * len, w * len); }

	float normalize_GetLength()
	{
		float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
		float len = 1.0f / length;
		v[0] *= len; v[1] *= len; v[2] *= len;
		return length;
	}
	float Dot(const Vec4& pVec) const
	{
		return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2] + v[3] * pVec.v[3];
	}
	float Dot(const Vec4& v1, const Vec4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
	Vec4 Max(const Vec4& v1, const Vec4& v2)
	{
		return Vec4(max(v1.v[0], v2.v[0]),
			max(v1.v[1], v2.v[1]),
			max(v1.v[2], v2.v[2]), max(v1.v[3], v2.v[3]));
	}
	float Max() const
	{
		return max(x, max(y, max(z, w)));
	}
	Vec4 Min(const Vec4& v1, const Vec4& v2)
	{
		return Vec4(min(v1.v[0], v2.v[0]),
			min(v1.v[1], v2.v[1]),
			min(v1.v[2], v2.v[2]), min(v1.v[3], v2.v[3]));
	}
	float Min() const
	{
		return min(x, min(y, min(z, w)));
	}
	Vec4 division() {
		return Vec4(x / w, y / w, z / w, 1.f);
	}
	Vec3 divisionTo3() {
		return Vec3(x / w, y / w, z / w);
	}
};

class Matrix
{
public:
	union
	{
		float a[4][4];
		float m[16];
	};
	Matrix() {
		a[0][0] = 1;
		a[1][0] = 0;
		a[2][0] = 0;
		a[3][0] = 0;
		a[0][1] = 0;
		a[1][1] = 1;
		a[2][1] = 0;
		a[3][1] = 0;
		a[0][2] = 0;
		a[1][2] = 0;
		a[2][2] = 1;
		a[3][2] = 0;
		a[0][3] = 0;
		a[1][3] = 0;
		a[2][3] = 0;
		a[3][3] = 1;
	}
	Matrix(float a00, float a10, float a20, float a30, float a01, float a11, float a21, float a31, float a02, float a12, float a22, float a32, float a03, float a13, float a23, float a33) {
		a[0][0] = a00;
		a[1][0] = a10;
		a[2][0] = a20;
		a[3][0] = a30;
		a[0][1] = a01;
		a[1][1] = a11;
		a[2][1] = a21;
		a[3][1] = a31;
		a[0][2] = a02;
		a[1][2] = a12;
		a[2][2] = a22;
		a[3][2] = a32;
		a[0][3] = a03;
		a[1][3] = a13;
		a[2][3] = a23;
		a[3][3] = a33;
	}
	void copy(const Matrix& matrix) {
		for (int i = 0; i < 16; i++) {
			m[i] = matrix.m[i];
		}
	}
	float& operator[](int i) {
		return m[i];
	}
	Vec3 mulPoint(const Vec3& v)
	{
		Vec3 v1 = Vec3(
			(v.x * m[0] + v.y * m[1] + v.z * m[2]) + m[3],
			(v.x * m[4] + v.y * m[5] + v.z * m[6]) + m[7],
			(v.x * m[8] + v.y * m[9] + v.z * m[10]) + m[11]);
		float w;
		w = (m[12] * v.x) + (m[13] * v.y) + (m[14] * v.z) + m[15];
		w = 1.0f / w;
		return (v1 * w);
	}
	Vec4 mulPoint(const Vec4& v)
	{
		Vec4 v1 = Vec4(
			v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3],
			v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7],
			v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11],
			v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15]);
		return v1;
	}
	Matrix mul(const Matrix& matrix) const
	{
		Matrix ret;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					ret.a[i][j] += a[i][k] * matrix.a[k][j];
				}
			}
		}
		return ret;
	}
	Matrix operator*(const Matrix& matrix)
	{
		return mul(matrix);
	}
	Matrix trans(float t1, float t2, float t3) {
		Matrix t;
		t.m[3] = t1;
		t.m[7] = t2;
		t.m[11] = t3;
		return t;
	}
	Vec3 Tanslation(const Vec3& v, float t1, float t2, float t3) {
		Vec3 v1 = trans(t1, t2, t2).mulPoint(v);
		return v1;
	}
	Matrix rot(std::string axis, float radian) {
		Matrix t;
		float sinr = sin(radian);
		float cosr = cos(radian);
		if (axis == "x" || axis == "X") {
			t.m[5] = cosr;
			t.m[6] = -sinr;
			t.m[9] = sinr;
			t.m[10] = cosr;
		}
		if (axis == "y" || axis == "Y") {
			t.m[0] = cosr;
			t.m[2] = sinr;
			t.m[8] = -sinr;
			t.m[10] = cosr;
		}
		if (axis == "z" || axis == "Z") {
			t.m[0] = cosr;
			t.m[1] = -sinr;
			t.m[4] = sinr;
			t.m[5] = cosr;
		}
	}
	Vec3 Rotation(const Vec3& v, std::string axis, float radian) {
		Vec3 v1 = rot(axis, radian).mulPoint(v);
		return v1;
	}
	Matrix scal(float t1, float t2, float t3) {
		Matrix t;
		t.m[3] *= t1;
		t.m[7] *= t2;
		t.m[11] *= t3;
		return t;
	}
	Vec3 Scaling(Vec3& v, float t1, float t2, float t3) {
		Vec3 v1 = scal(t1, t2, t3).mulPoint(v);
		return v1;
	}
	Matrix Transpose() const {
		Matrix t;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				t.a[i][j] = a[j][i];
			}
		}
		return t;
	}

	Matrix invert()
	{
		Matrix inv;
		inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
		inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
		inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
		float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
		if (det == 0) {
			// Handle this case
		}
		det = 1.0 / det;
		for (int i = 0; i < 16; i++) {
			inv[i] = inv[i] * det;
		}
		return inv;
	}
	Matrix getLookAt(Vec3& from, Vec3& to, Vec3& up) {
		Vec3 dir = (from - to) / from.distanceTo(to);
		Vec3 right = up.Cross(dir);
		Vec3 rup = dir.Cross(right);
		Matrix m;
		m[0] = right.x;
		m[1] = right.y;
		m[2] = right.z;
		m[3] = -from.Dot(right);
		m[4] = rup.x;
		m[5] = rup.y;
		m[6] = rup.z;
		m[7] = -from.Dot(rup);
		m[8] = dir.x;
		m[9] = dir.y;
		m[10] = dir.z;
		m[11] = -from.Dot(dir);
		m[12] = 0.f;
		m[13] = 0.f;
		m[14] = 0.f;
		m[15] = 1.f;
		/*for (int i = 0;i < 16;i++) {
			std::cout << m[i] << "\n";
		}*/
		return m;
	}
};
