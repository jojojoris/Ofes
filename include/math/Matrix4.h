/*
 * Matrix4.h
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

namespace Ofes {
namespace Math {

class Matrix4 {
public:
	Matrix4();
	virtual ~Matrix4();

	Matrix4& operator=(const Matrix4& m);
	Matrix4 operator*(const Matrix4& right);
	Matrix4& operator*=(const Matrix4& right);

	void identity();
	void zero();
	void one();

	void multiply(const Matrix4* m);

	union _matrix {
		float m[16];
		struct {
			float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23,
					m30, m31, m32, m33;
		};
	} matrix
#ifdef PSP
	__attribute__((aligned(16)))
#endif
	;
private:
};

}
}

#endif /* MATRIX4_H_ */
