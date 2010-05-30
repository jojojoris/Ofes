/*
 * Matrix4.cpp
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#include <math/Matrix4.h>

#ifdef PSP

using namespace Ofes;
using namespace Math;

Matrix4::Matrix4() {
	identity();
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
	__asm__ volatile (
			"vmidt.q    M000\n"
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]));
}

void Matrix4::zero() {
	__asm__ volatile (
			"vmzero.q    M000\n"
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]));

}

void Matrix4::one() {
	__asm__ volatile (
			"vmone.q    M000\n"
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]));

}

void Matrix4::multiply(const Matrix4* m) {
	__asm__ volatile (
			"lv.q       C000,  0  + %0\n"
			"lv.q       C010,  16 + %0\n"
			"lv.q       C020,  32 + %0\n"
			"lv.q       C030,  48 + %0\n"
			"lv.q       C100,  0  + %1\n"
			"lv.q       C110,  16 + %1\n"
			"lv.q       C120,  32 + %1\n"
			"lv.q       C130,  48 + %1\n"
			"vmmul.q    M200,  M000,  M100\n"
			"sv.q       C200,  0  + %0\n"
			"sv.q       C210,  16 + %0\n"
			"sv.q       C220,  32 + %0\n"
			"sv.q       C230,  48 + %0\n"
			:"+m"(matrix.m[0]):"m"(m->matrix.m[0]));
}

void Matrix4::rotateX(float rad) {
	__asm__ volatile (
			//Load rad in register S200 and convert it to a usable value.
			"mtv        %1, S000\n"
			"vcst.s     S001, VFPU_2_PI\n"
			"vmul.s     S000, S000, S001\n"
			//Create identity matrix in M000
			"vmidt.q    M200\n"
			//Create x rotation matrix
			"vrot.q     C210, S000, [0, c, s, 0]\n"
			"vrot.q     C220, S000, [0,-s, c, 0]\n"
			//Load original matrix
			"lv.q       C100,  0  + %0\n"
			"lv.q       C110,  16 + %0\n"
			"lv.q       C120,  32 + %0\n"
			"lv.q       C130,  48 + %0\n"
			//Multiply M100 with M000 and put result in M200
			"vmmul.q    M000,  M100,  M200\n"
			//Place result in original matrix
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]):"r"(rad));
}

void Matrix4::rotateY(float rad) {
	__asm__ volatile (
			//Load rad in register S200 and convert it to a usable value.
			"mtv        %1, S000\n"
			"vcst.s     S001, VFPU_2_PI\n"
			"vmul.s     S000, S000, S001\n"
			//Create identity matrix in M000
			"vmidt.q    M200\n"
			//Create y rotation matrix
			"vrot.q  C200, S000, [c, 0,-s, 0]\n"
			"vrot.q  C220, S000, [s, 0, c, 0]\n"
			//Load original matrix
			"lv.q       C100,  0  + %0\n"
			"lv.q       C110,  16 + %0\n"
			"lv.q       C120,  32 + %0\n"
			"lv.q       C130,  48 + %0\n"
			//Multiply M100 with M000 and put result in M200
			"vmmul.q    M000,  M100,  M200\n"
			//Place result in original matrix
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]):"r"(rad));
}

void Matrix4::rotateZ(float rad) {
	__asm__ volatile (
			//Load rad in register S200 and convert it to a usable value.
			"mtv        %1, S000\n"
			"vcst.s     S001, VFPU_2_PI\n"
			"vmul.s     S000, S000, S001\n"
			//Create identity matrix in M000
			"vmidt.q    M200\n"
			//Create z rotation matrix
			"vrot.q  C200, S000, [ c, s, 0, 0]\n"
			"vrot.q  C210, S000, [-s, c, 0, 0]\n"
			//Load original matrix
			"lv.q       C100,  0  + %0\n"
			"lv.q       C110,  16 + %0\n"
			"lv.q       C120,  32 + %0\n"
			"lv.q       C130,  48 + %0\n"
			//Multiply M100 with M000 and put result in M200
			"vmmul.q    M000,  M100,  M200\n"
			//Place result in original matrix
			"sv.q       C000,  0  + %0\n"
			"sv.q       C010,  16 + %0\n"
			"sv.q       C020,  32 + %0\n"
			"sv.q       C030,  48 + %0\n"
			:"+m"(matrix.m[0]):"r"(rad));
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
	__asm__ volatile (
			//Create identity matrix in M000
			"vmidt.q    M000\n"
			//Load the coordinates into S000, S001, S002
			//This is now the translation matrix
			"mtv        %1, S030\n"
			"mtv        %2, S031\n"
			"mtv        %3, S032\n"
			//Load matrix into M100
			"lv.q       C100,  0  + %0\n"
			"lv.q       C110,  16 + %0\n"
			"lv.q       C120,  32 + %0\n"
			"lv.q       C130,  48 + %0\n"
			//Multiply M100 with M000 and put result in M200
			"vmmul.q    M200,  M100,  M000\n"
			//Place result in original matrix
			"sv.q       C200,  0  + %0\n"
			"sv.q       C210,  16 + %0\n"
			"sv.q       C220,  32 + %0\n"
			"sv.q       C230,  48 + %0\n"
			:"+m"(matrix.m[0]):"r"(x), "r"(y), "r"(z));
}

void Matrix4::ortho(float left, float right, float bottom, float top,
		float nearVal, float farVal) {
	__asm__ volatile (
			//Create ortho matrix in M100
			"vmidt.q M100\n"
			"mtv     %2, S000\n"
			"mtv     %4, S001\n"
			"mtv     %6, S002\n"
			"mtv     %1, S010\n"
			"mtv     %3, S011\n"
			"mtv     %5, S012\n"
			"vsub.t  C020, C000, C010\n"
			"vrcp.t  C020, C020\n"
			"vmul.s  S100, S100[2], S020\n"
			"vmul.s  S111, S111[2], S021\n"
			"vmul.s  S122, S122[2], S022[-x]\n"
			"vsub.t  C130, C000[-x,-y,-z], C010\n"
			"vmul.t  C130, C130, C020\n"

			//Load matrix into M000
			"lv.q       C000,  0  + %0\n"
			"lv.q       C010,  16 + %0\n"
			"lv.q       C020,  32 + %0\n"
			"lv.q       C030,  48 + %0\n"
			//Multiply M100 with M000 and put result in M200
			"vmmul.q    M200,  M100,  M000\n"
			//Place result in original matrix
			"sv.q       C200,  0  + %0\n"
			"sv.q       C210,  16 + %0\n"
			"sv.q       C220,  32 + %0\n"
			"sv.q       C230,  48 + %0\n"
			:"+m"(matrix.m[0]):"r"(left),"r"(right),"r"(bottom),"r"(top),"r"(nearVal),"r"(farVal));
}

#endif //PSP
