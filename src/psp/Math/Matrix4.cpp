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

#endif //PSP
