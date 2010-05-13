/*
 * Matrix4.cpp
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#include <math/Matrix4.h>

#ifdef GENERIC

using namespace Ofes;
using namespace Math;

Matrix4::Matrix4() {
	zero();
}

Matrix4::~Matrix4() {
}

Matrix4& Matrix4::operator=(const Matrix4& m) {
        matrix=m.matrix;
        return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m){
        Matrix4 res = *this;
        res.multiply(&m);
        return res;
}

Matrix4& Matrix4::operator*=(const Matrix4& m){
        multiply(&m);
        return *this;
}

void Matrix4::identity() {
	matrix.m[1] = matrix.m[2] = matrix.m[3] = matrix.m[4] = matrix.m[6]
			= matrix.m[7] = matrix.m[8] = matrix.m[9] = matrix.m[11]
					= matrix.m[12] = matrix.m[13] = matrix.m[14] = 0.0f;

	matrix.m[0] = matrix.m[5] = matrix.m[10] = matrix.m[15] = 1.0f;
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
	tmp.matrix.m00 = (matrix.m00 * m->matrix.m00)
			+ (matrix.m01 * m->matrix.m10) + (matrix.m02 * m->matrix.m20)
			+ (matrix.m03 * m->matrix.m30);

	tmp.matrix.m01 = (matrix.m00 * m->matrix.m01)
			+ (matrix.m01 * m->matrix.m11) + (matrix.m02 * m->matrix.m21)
			+ (matrix.m03 * m->matrix.m31);

	tmp.matrix.m02 = (matrix.m00 * m->matrix.m02)
			+ (matrix.m01 * m->matrix.m12) + (matrix.m02 * m->matrix.m22)
			+ (matrix.m03 * m->matrix.m32);

	tmp.matrix.m03 = (matrix.m00 * m->matrix.m03)
			+ (matrix.m01 * m->matrix.m13) + (matrix.m02 * m->matrix.m23)
			+ (matrix.m03 * m->matrix.m33);

	tmp.matrix.m10 = (matrix.m10 * m->matrix.m00)
			+ (matrix.m11 * m->matrix.m10) + (matrix.m12 * m->matrix.m20)
			+ (matrix.m13 * m->matrix.m30);

	tmp.matrix.m11 = (matrix.m10 * m->matrix.m01)
			+ (matrix.m11 * m->matrix.m11) + (matrix.m12 * m->matrix.m21)
			+ (matrix.m13 * m->matrix.m31);

	tmp.matrix.m12 = (matrix.m10 * m->matrix.m02)
			+ (matrix.m11 * m->matrix.m12) + (matrix.m12 * m->matrix.m22)
			+ (matrix.m13 * m->matrix.m32);

	tmp.matrix.m13 = (matrix.m10 * m->matrix.m03)
			+ (matrix.m11 * m->matrix.m13) + (matrix.m12 * m->matrix.m23)
			+ (matrix.m13 * m->matrix.m33);

	tmp.matrix.m20 = (matrix.m20 * m->matrix.m00)
			+ (matrix.m21 * m->matrix.m10) + (matrix.m22 * m->matrix.m20)
			+ (matrix.m23 * m->matrix.m30);

	tmp.matrix.m21 = (matrix.m20 * m->matrix.m01)
			+ (matrix.m21 * m->matrix.m11) + (matrix.m22 * m->matrix.m21)
			+ (matrix.m23 * m->matrix.m31);

	tmp.matrix.m22 = (matrix.m20 * m->matrix.m02)
			+ (matrix.m21 * m->matrix.m12) + (matrix.m22 * m->matrix.m22)
			+ (matrix.m23 * m->matrix.m32);

	tmp.matrix.m23 = (matrix.m20 * m->matrix.m03)
			+ (matrix.m21 * m->matrix.m13) + (matrix.m22 * m->matrix.m23)
			+ (matrix.m23 * m->matrix.m33);

	tmp.matrix.m30 = (matrix.m30 * m->matrix.m00)
			+ (matrix.m31 * m->matrix.m10) + (matrix.m32 * m->matrix.m20)
			+ (matrix.m33 * m->matrix.m30);

	tmp.matrix.m31 = (matrix.m30 * m->matrix.m01)
			+ (matrix.m31 * m->matrix.m11) + (matrix.m32 * m->matrix.m21)
			+ (matrix.m33 * m->matrix.m31);

	tmp.matrix.m32 = (matrix.m30 * m->matrix.m02)
			+ (matrix.m31 * m->matrix.m12) + (matrix.m32 * m->matrix.m22)
			+ (matrix.m33 * m->matrix.m32);

	tmp.matrix.m33 = (matrix.m30 * m->matrix.m03)
			+ (matrix.m31 * m->matrix.m13) + (matrix.m32 * m->matrix.m23)
			+ (matrix.m33 * m->matrix.m33);

	matrix=tmp.matrix;
}

#endif //GENERIC
