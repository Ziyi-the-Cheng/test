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
	/*n = 2 -> 2D Graphics
	  n = 3->Rotations, Shading Frames, Translate in 2D
	  n = 4->Transformations, 3D Projection*/

public:
	union
	{
		float a[4][4];
		float m[16];
	};
	Matrix() { identity(); }
	Matrix(float* otherMatrix) {
		memcpy(&m, otherMatrix, 16 * sizeof(float));
	}
	Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
	{
		a[0][0] = m00; a[0][1] = m01; a[0][2] = m02; a[0][3] = m03;
		a[1][0] = m10; a[1][1] = m11; a[1][2] = m12; a[1][3] = m13;
		a[2][0] = m20; a[2][1] = m21; a[2][2] = m22; a[2][3] = m23;
		a[3][0] = m30; a[3][1] = m31; a[3][2] = m32; a[3][3] = m33;
	}
	//Matrix() { translation(); }

	Matrix operator*(const Matrix& matrix)
	{
		return mul(matrix);
	}

	float& operator[](int i) { return m[i]; }

	void identity() {
		memset(m, 0, 16 * sizeof(float));
		m[0] = 1.0f;
		m[5] = 1.0f;
		m[10] = 1.0f;
		m[15] = 1.0f;
	}

	//void translation(float t1, float t2, float t3) {
	//	m[0] = 1.0f;
	//	m[5] = 1.0f;
	//	m[10] = 1.0f;
	//	m[15] = 1.0f;
	//	m[3] = t1;
	//	m[7] = t2;
	//	m[11] = t3;
	//}

	Vec3 mulPoint(const Vec3& v)
	{
		Vec3 v1 = Vec3(
			(v.x * m[0] + v.y * m[1] + v.z * m[2]) + m[3],
			(v.x * m[4] + v.y * m[5] + v.z * m[6]) + m[7],
			(v.x * m[8] + v.y * m[9] + v.z * m[10]) + m[11]);
		//每一行的前三个元素用于乘以 v 的 x, y, z 分量，第 4 个元素用于加上一个平移分量。
		//这些运算相当于将向量 v 通过3x3线性变换矩阵旋转、缩放，再加上平移分量 m[3], m[7], m[11]。
		float w;
		w = (m[12] * v.x) + (m[13] * v.y) + (m[14] * v.z) + m[15];
		//w 分量是齐次坐标的第四分量，计算公式为 w = (m[12] * v.x) + (m[13] * v.y) + (m[14] * v.z) + m[15]。
		//在投影或透视变换中，w 用于描述深度信息或投影缩放。
		w = 1.0f / w;
		return (v1 * w);
		/*将 w 求倒数并乘以 v1，相当于对 v1 的每个分量除以 w，
		这是将 v1 从齐次坐标系归一化到直角坐标系的过程。对于投影变换，归一化后可以得到正确的3D空间位置或2D投影位置。
		相当于从齐次坐标（x, y, z, w）转化成三维空间坐标（x/w, y/w, z/w）
		方法的几何意义：
		仿射和投影变换: 这个函数可以实现旋转、缩放、平移（由矩阵 m 定义的仿射变换），并支持齐次坐标的投影转换。
		投影缩放: 齐次坐标归一化的 w 分量会影响深度缩放，使得近大远小的投影效果得以实现。*/
	}
	//Vec3 mulPoint(const Vec3& v)
	//{
	//	return Vec3(
	//		(v.x * m[0] + v.y * m[1] + v.z * m[2]) + m[3],
	//		(v.x * m[4] + v.y * m[5] + v.z * m[6]) + m[7],
	//		(v.x * m[8] + v.y * m[9] + v.z * m[10]) + m[11]);
	//}
	//只进行旋转的情况下，w = 0：
	Vec3 mulVec(const Vec3& v)
	{
		return Vec3(
			(v.x * m[0] + v.y * m[1] + v.z * m[2]),
			(v.x * m[4] + v.y * m[5] + v.z * m[6]),
			(v.x * m[8] + v.y * m[9] + v.z * m[10]));
	}

	static Matrix translation(const Vec3& v) {
		Matrix mat;
		mat.a[0][3] = v.x;
		mat.a[1][3] = v.y;
		mat.a[2][3] = v.z;
		return mat;
	}

	static Matrix scale(const Vec3& v) {
		Matrix mat;
		mat.m[0] = v.x;
		mat.m[5] = v.y;
		mat.m[10] = v.z;
		return mat;
	}

	static Matrix rotateX(float theta) {
		Matrix mat;
		float ct = cosf(theta);
		float st = sinf(theta);
		mat.m[5] = ct;
		mat.m[6] = -st;
		mat.m[9] = st;
		mat.m[10] = ct;
		return mat;
	}

	static Matrix rotateY(float theta) {
		Matrix mat;
		float ct = cosf(theta);
		float st = sinf(theta);
		mat.m[0] = ct;
		mat.m[2] = st;
		mat.m[8] = -st;
		mat.m[10] = ct;
		return mat;
	}

	static Matrix rotateZ(float theta) {
		Matrix mat;
		float ct = cosf(theta);
		float st = sinf(theta);
		mat.m[0] = ct;
		mat.m[1] = -st;
		mat.m[4] = st;
		mat.m[5] = ct;
		return mat;
	}


	Matrix mul(const Matrix& matrix) const
	{
		Matrix ret;
		ret.m[0] = m[0] * matrix.m[0] + m[4] * matrix.m[1] + m[8] * matrix.m[2] + m[12] * matrix.m[3];
		ret.m[1] = m[1] * matrix.m[0] + m[5] * matrix.m[1] + m[9] * matrix.m[2] + m[13] * matrix.m[3];
		ret.m[2] = m[2] * matrix.m[0] + m[6] * matrix.m[1] + m[10] * matrix.m[2] + m[14] * matrix.m[3];
		ret.m[3] = m[3] * matrix.m[0] + m[7] * matrix.m[1] + m[11] * matrix.m[2] + m[15] * matrix.m[3];
		ret.m[4] = m[0] * matrix.m[4] + m[4] * matrix.m[5] + m[8] * matrix.m[6] + m[12] * matrix.m[7];
		ret.m[5] = m[1] * matrix.m[4] + m[5] * matrix.m[5] + m[9] * matrix.m[6] + m[13] * matrix.m[7];
		ret.m[6] = m[2] * matrix.m[4] + m[6] * matrix.m[5] + m[10] * matrix.m[6] + m[14] * matrix.m[7];
		ret.m[7] = m[3] * matrix.m[4] + m[7] * matrix.m[5] + m[11] * matrix.m[6] + m[15] * matrix.m[7];
		ret.m[8] = m[0] * matrix.m[8] + m[4] * matrix.m[9] + m[8] * matrix.m[10] + m[12] * matrix.m[11];
		ret.m[9] = m[1] * matrix.m[8] + m[5] * matrix.m[9] + m[9] * matrix.m[10] + m[13] * matrix.m[11];
		ret.m[10] = m[2] * matrix.m[8] + m[6] * matrix.m[9] + m[10] * matrix.m[10] + m[14] * matrix.m[11];
		ret.m[11] = m[3] * matrix.m[8] + m[7] * matrix.m[9] + m[11] * matrix.m[10] + m[15] * matrix.m[11];
		ret.m[12] = m[0] * matrix.m[12] + m[4] * matrix.m[13] + m[8] * matrix.m[14] + m[12] * matrix.m[15];
		ret.m[13] = m[1] * matrix.m[12] + m[5] * matrix.m[13] + m[9] * matrix.m[14] + m[13] * matrix.m[15];
		ret.m[14] = m[2] * matrix.m[12] + m[6] * matrix.m[13] + m[10] * matrix.m[14] + m[14] * matrix.m[15];
		ret.m[15] = m[3] * matrix.m[12] + m[7] * matrix.m[13] + m[11] * matrix.m[14] + m[15] * matrix.m[15];
		return ret;
	}

	//Matrix operator*(const Matrix& matrix)
	//{
	//	return mul(matrix);
	//}

	Matrix transpose() {
		Matrix mat;
		mat.m[0] = m[0];
		mat.m[1] = m[4];
		mat.m[2] = m[8];
		mat.m[3] = m[12];
		mat.m[4] = m[1];
		mat.m[5] = m[5];
		mat.m[6] = m[9];
		mat.m[7] = m[13];
		mat.m[8] = m[2];
		mat.m[9] = m[6];
		mat.m[10] = m[10];
		mat.m[11] = m[14];
		mat.m[12] = m[3];
		mat.m[13] = m[7];
		mat.m[14] = m[11];
		mat.m[15] = m[15];
		return mat;
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

	Matrix PerPro(float height, float width, float radians, float Far, float Near) {
		Matrix PerPro;

		PerPro[0] = 1 / (tan(radians / 2) * (width / height));
		PerPro[1] = 0;
		PerPro[2] = 0;
		PerPro[3] = 0;
		PerPro[4] = 0;
		PerPro[5] = 1 / tan(radians / 2);
		PerPro[6] = 0;
		PerPro[7] = 0;
		PerPro[8] = 0;
		PerPro[9] = 0;
		PerPro[10] = (-Far) / (Far - Near);
		PerPro[11] = ((-Far) * Near) / (Far - Near);
		PerPro[12] = 0;
		PerPro[13] = 0;
		PerPro[14] = -1;
		PerPro[15] = 0;
		return PerPro;
	}

	Vec3 MapToScreen(float px, float py, float width, float height) {
		return Vec3(((px + 1) / 2) * width, ((py + 1) / 2) * height, 1);
	}

	Matrix lookAt(Vec3& from, Vec3& to, Vec3& up) {
		Vec3 dir = (from - to).normalize();
		Vec3 right = up.Cross(dir).normalize();
		Vec3 upPrime = dir.Cross(right);
		Matrix result;

		result.m[0] = right.x;
		result.m[1] = right.y;
		result.m[2] = right.z;

		result.m[4] = upPrime.x;
		result.m[5] = upPrime.y;
		result.m[6] = upPrime.z;

		result.m[8] = dir.x;
		result.m[9] = dir.y;
		result.m[10] = dir.z;

		result.m[3] = -from.Dot(right);
		result.m[7] = -from.Dot(upPrime);
		result.m[11] = -from.Dot(dir);

		result.m[12] = 0.f;
		result.m[13] = 0.f;
		result.m[14] = 0.f;
		result.m[15] = 1.f;

		return result;
	}
};
