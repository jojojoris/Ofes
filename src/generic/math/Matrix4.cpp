/*
 * Matrix4.cpp
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#include <math/Matrix4.h>

#ifndef GENERIC

#include <math.h>

using namespace Ofes;
using namespace Math;

Matrix4::Matrix4() {
	zero();
}

Matrix4::~Matrix4() {
}

Matrix4& Matrix4::operator=(const Matrix4& m) {
	matrix = m.matrix;
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m) {
	Matrix4 res = *this;
	res.multiply(&m);
	return res;
}

Matrix4& Matrix4::operator*=(const Matrix4& m) {
	multiply(&m);
	return *this;
}

void Matrix4::identity() {
	matrix.m01 = matrix.m01 = matrix.m03 = matrix.m10 = matrix.m12 = matrix.m13
			= matrix.m20 = matrix.m21 = matrix.m23 = matrix.m30 = matrix.m31
					= matrix.m32 = 0.0f;

	matrix.m00 = matrix.m11 = matrix.m22 = matrix.m33 = 1.0f;
}

void Matrix4::zero() {
	matrix.m[0] = matrix.m[1] = matrix.m[2] = matrix.m[3] = matrix.m[4]
			= matrix.m[5] = matrix.m[6] = matrix.m[7] = matrix.m[8]
					= matrix.m[9] = matrix.m[10] = matrix.m[11] = matrix.m[12]
							= matrix.m[13] = matrix.m[14] = matrix.m[15] = 0.0f;
}

void Matrix4::one() {
	matrix.m[0] = matrix.m[1] = matrix.m[2] = matrix.m[3] = matrix.m[4]
			= matrix.m[5] = matrix.m[6] = matrix.m[7] = matrix.m[8]
					= matrix.m[9] = matrix.m[10] = matrix.m[11] = matrix.m[12]
							= matrix.m[13] = matrix.m[14] = matrix.m[15] = 1.0f;
}

void Matrix4::multiply(const Matrix4* m) {
	Matrix4 tmp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float v = 0.0f;
			for (int k = 0; k < 4; ++k)
				v += matrix.m[(k << 2) + j] * m->matrix.m[(i << 2) + k];
			tmp.matrix.m[(i << 2) + j] = v;
		}
	}
	matrix = tmp.matrix;
}

void Matrix4::rotateX(float rad) {
	Matrix4 tmp;
	float f_Sin = sinf(rad);
	float f_Cos = cosf(rad);
	tmp.identity();
	tmp.matrix.m11 = f_Cos;
	tmp.matrix.m12 = f_Sin;
	tmp.matrix.m22 = f_Cos;
	tmp.matrix.m21 = -f_Sin;
	multiply(&tmp);
}

void Matrix4::rotateY(float rad) {
	Matrix4 tmp;
	float f_Sin = sinf(rad);
	float f_Cos = cosf(rad);
	tmp.identity();
	tmp.matrix.m00 = f_Cos;
	tmp.matrix.m02 = -f_Sin;
	tmp.matrix.m22 = f_Cos;
	tmp.matrix.m20 = f_Sin;
	multiply(&tmp);
}

void Matrix4::rotateZ(float rad) {
	Matrix4 tmp;
	float f_Sin = sinf(rad);
	float f_Cos = cosf(rad);
	tmp.identity();
	tmp.matrix.m00 = f_Cos;
	tmp.matrix.m01 = f_Sin;
	tmp.matrix.m11 = f_Cos;
	tmp.matrix.m10 = -f_Sin;
	multiply(&tmp);
}

void Matrix4::rotateXY(float rad) {
	rotateX(rad);
	rotateY(rad);
}

void Matrix4::rotateXZ(float rad) {
	rotateX(rad);
	rotateZ(rad);
}

void Matrix4::rotateYZ(float rad) {
	rotateY(rad);
	rotateZ(rad);
}

void Matrix4::rotateXYZ(float rad) {
	rotateX(rad);
	rotateY(rad);
	rotateZ(rad);
}

void Matrix4::translate(float x, float y, float z) {
	Matrix4 tmp;
	tmp.identity();
	tmp.matrix.m30 = x;
	tmp.matrix.m31 = y;
	tmp.matrix.m32 = z;
	multiply(&tmp);
}

#endif //GENERIC
