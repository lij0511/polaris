
#ifndef POLA_GRAPHIC_MATRIX4_H
#define POLA_GRAPHIC_MATRIX4_H

#include "graphic/Vector.h"

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

    enum Entry {
        kScaleX = 0,
        kSkewY = 1,
        kPerspective0 = 3,
        kSkewX = 4,
        kScaleY = 5,
        kPerspective1 = 7,
        kScaleZ = 10,
        kTranslateX = 12,
        kTranslateY = 13,
        kTranslateZ = 14,
        kPerspective2 = 15
    };

    // NOTE: The flags from kTypeIdentity to kTypePerspective
    //       must be kept in sync with the type flags found
    //       in SkMatrix
    enum Type {
        kTypeIdentity = 0,
        kTypeTranslate = 0x1,
        kTypeScale = 0x2,
        kTypeAffine = 0x4,
        kTypePerspective = 0x8,
        kTypeRectToRect = 0x10,
        kTypeUnknown = 0x20,
    };

    static const int sGeometryMask = 0xf;

    Matrix4() {
        loadIdentity();
    }

    Matrix4(const float* v) {
        load(v);
    }

    Matrix4(const Matrix4& v) {
        load(v);
    }

    float operator[](int index) const {
        return data[index];
    }

    float& operator[](int index) {
        mType = kTypeUnknown;
        return data[index];
    }

    bool operator==(const Matrix4& b) {
        return !memcmp(&data[0], &b.data[0], 16 * sizeof(float));
    }

    bool operator!=(const Matrix4& b) {
        return !(*this == b);
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
    void loadPerspective(float fovy, float aspect, float near, float far);
    void loadLookAt(vec3& position, vec3& target, vec3& upper);

    uint8_t getType() const;

    void multiply(const Matrix4& v) {
        Matrix4 u;
        u.loadMultiply(*this, v);
        load(u);
    }

    void multiply(float v);

    void translate(float x, float y, float z = 0) {
        if ((getType() & sGeometryMask) <= kTypeTranslate) {
            data[kTranslateX] += x;
            data[kTranslateY] += y;
            data[kTranslateZ] += z;
            mType |= kTypeUnknown;
        } else {
            // Doing a translation will only affect the translate bit of the type
            // Save the type
            uint8_t type = mType;

            Matrix4 u;
            u.loadTranslate(x, y, z);
            multiply(u);

            // Restore the type and fix the translate bit
            mType = type;
            if (data[kTranslateX] != 0.0f || data[kTranslateY] != 0.0f) {
                mType |= kTypeTranslate;
            } else {
                mType &= ~kTypeTranslate;
            }
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

    /**
     * If the matrix is identity or translate and/or scale.
     */
    bool isSimple() const;
    bool isPureTranslate() const;
    bool isIdentity() const;
    bool isPerspective() const;
    bool rectToRect() const;
    bool positiveScale() const;

    bool changesBounds() const;

    void copyTo(float* v) const;

    float mapZ(const Vector3& orig) const;
    void mapPoint3d(Vector3& vec) const;
    void mapPoint(float& x, float& y) const; // 2d only

    float getTranslateX() const;
    float getTranslateY() const;

    void decomposeScale(float& sx, float& sy) const;

    static const Matrix4& identity();

private:
    mutable uint8_t mType;

    inline float get(int i, int j) const {
        return data[i * 4 + j];
    }

    inline void set(int i, int j, float v) {
        data[i * 4 + j] = v;
    }

    uint8_t getGeometryType() const;

}; // class Matrix4

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

typedef Matrix4 mat4;

}
};

#endif // ANDROID_HWUI_MATRIX_H