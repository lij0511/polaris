
#ifndef POLA_GRAPHIC_MATRIX4_H
#define POLA_GRAPHIC_MATRIX4_H

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Quaternion.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

namespace pola {
namespace graphic {

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class Matrix4 {
public:
    float data[16];

    Matrix4() {
        loadIdentity();
    }

    Matrix4(const float* v) {
        load(v);
    }

    Matrix4(const Matrix4& v) {
        load(v);
    }

    Matrix4(const Vector3& position, const Vector3& rotation, const Vector3& scale) {
    	compose(position, rotation, scale);
    }

    Matrix4(const Vector3& position, const Quaternion& quaternion, const Vector3& scale) {
    	compose(position, quaternion, scale);
    }

    float operator[](int index) const {
        return data[index];
    }

    float& operator[](int index) {
        return data[index];
    }

    bool operator==(const Matrix4& b) {
        return !memcmp(&data[0], &b.data[0], 16 * sizeof(float));
    }

    bool operator!=(const Matrix4& b) {
        return !(*this == b);
    }

    Matrix4 operator *(const Matrix4& b) const {
    	Matrix4 m;
    	m.loadMultiply(*this, b);
    	return m;
    }

    Matrix4& operator *=(const Matrix4& b) {
		Matrix4 m;
		m.loadMultiply(*this, b);
		load(m);
		return *this;
	}

    void loadIdentity();

    void load(const float* v);
    void load(const Matrix4& v);

    void loadInverse(const Matrix4& v);

    void loadTranslate(float x, float y, float z);
    void loadScale(float sx, float sy, float sz);
    void loadSkew(float sx, float sy);
    void loadRotate(float angle);
    void loadRotate(float angle, float x, float y, float z);
    void loadMultiply(const Matrix4& u, const Matrix4& v);

    void loadOrtho(float left, float right, float bottom, float top, float near, float far);

    void multiply(const Matrix4& v) {
        Matrix4 u;
        u.loadMultiply(*this, v);
        load(u);
    }

    void multiply(float v);

    void translate(float x, float y, float z = 0) {
        if (false) {
            data[12] += x;
            data[13] += y;
            data[14] += z;
        } else {
            Matrix4 u;
            u.loadTranslate(x, y, z);
            multiply(u);
        }
    }

    void scale(float sx, float sy, float sz) {
        Matrix4 u;
        u.loadScale(sx, sy, sz);
        multiply(u);
    }

    void skew(float sx, float sy) {
        Matrix4 u;
        u.loadSkew(sx, sy);
        multiply(u);
    }

    void rotate(float angle, float x, float y, float z) {
        Matrix4 u;
        u.loadRotate(angle, x, y, z);
        multiply(u);
    }

    void copyTo(float* v) const;

    float mapZ(const Vector3& orig) const;
    void mapPoint3d(Vector3& vec) const;
    void mapPoint(float& x, float& y) const; // 2d only

    float getTranslateX() const;
    float getTranslateY() const;

    bool isIdentity() const;

    void setRotationRadians(const Vector3& radians);
    void setRotationDegrees(const Vector3& degrees);
    void transformVector(Vector3& vec) const;
    void transformVector(const Vector3& in, Vector3& out) const;

    void setPosition(const Vector3& position);
	void setScale(const Vector3& scale);
	void makeRotationFromQuaternion(const Quaternion& rotation);

    void compose(const Vector3& position, const Quaternion& quaternion, const Vector3& scale);
    void compose(const Vector3& position, const Vector3& rotation, const Vector3& scale);
    void decompose(Vector3& position, Quaternion& quaternion, Vector3& scale);
    void getRotation(Quaternion& rotation);

    void makeOrtho(float left, float right, float bottom, float top, float near, float far);
    void makeFrustum(float left, float right, float bottom, float top,
            float near, float far);
    void makePerspective(float fovy, float aspect, float near, float far);
    void lookAt(const vec3& eye, const vec3& target, const vec3& upper);

    static const Matrix4& identity();

private:

    float determinant();

    inline float get(int i, int j) const {
        return data[i * 4 + j];
    }

    inline void set(int i, int j, float v) {
        data[i * 4 + j] = v;
    }

}; // class Matrix4

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

typedef Matrix4 mat4;

}
};

#endif // ANDROID_HWUI_MATRIX_H
