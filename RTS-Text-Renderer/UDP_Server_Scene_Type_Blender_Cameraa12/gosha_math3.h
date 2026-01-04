//
// Created by k10 on 8/24/2025.
//

#ifndef GPS_GAME1_GOSHA_MATH3_H
#define GPS_GAME1_GOSHA_MATH3_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

//#include <iostream>
#include <array>
//#include <cmath>
#include <limits>
#include <utility>

// Forward declaration of Vec3
// This tells the compiler that Vec3 is a struct, which allows
// us to use it in function signatures without its full definition.
//struct Vec3;

#include "gosha_math2.h"

// ====================================================================
// --- A SIMPLE QUATERNION CLASS ---
// This class is essential for handling rotations without gimbal lock.
// It stores a rotation as a 4D vector (x, y, z, w).
// ====================================================================
struct Quaternion {
    float x, y, z, w;

    // Default constructor (identity quaternion)
    Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

    // Constructor with values
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    // Create a quaternion from an axis and an angle
    /*
    static Quaternion fromAxisAngle(const Vec3& axis, float angleRad) {
        float halfAngle = angleRad * 0.5f;
        float s = std::sin(halfAngle);
        float c = std::cos(halfAngle);
        Vec3 nAxis = axis.normalize();
        return Quaternion(nAxis.x * s, nAxis.y * s, nAxis.z * s, c);
    }
    */
    // Create a quaternion from an axis and an angle
    static Quaternion fromAxisAngle(const Vec3& axis, float angleRad) {
        float halfAngle = angleRad * 0.5f;
        float s = std::sin(halfAngle);
        float c = std::cos(halfAngle);

        // The compiler now knows what Vec3 is and that it has a normalize() method.
        Vec3 nAxis = axis.normalize();

        return Quaternion(nAxis.x * s, nAxis.y * s, nAxis.z * s, c);
    }

    // Quaternion multiplication
    // The order is important: q1 * q2 applies q2 first, then q1.
    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    // Normalize the quaternion
    void normalize() {
        float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
        if (magnitude > 0.0f) {
            float invMag = 1.0f / magnitude;
            x *= invMag;
            y *= invMag;
            z *= invMag;
            w *= invMag;
        }
    }

    // NEW: Get the conjugate of the quaternion
    Quaternion conjugate() const {
        return Quaternion(-x, -y, -z, w);
    }

    // NEW: Get the inverse of the quaternion.
    // For a unit quaternion, inverse is the same as the conjugate.
    // Since we'll be normalizing our quaternions, this is safe.
    Quaternion inverse() const {
        return conjugate();
    }




};
/**
   * @brief Creates a rotation matrix from a Quaternion.
   * @param q The Quaternion to convert.
   * @return A new Mat4 object representing the rotation.
   */
static Mat4 fromQuat(const Quaternion& q) {
    Mat4 out;
    const float x = q.x, y = q.y, z = q.z, w = q.w;
    const float x2 = x + x, y2 = y + y, z2 = z + z;
    const float xx = x * x2, xy = x * y2, xz = x * z2;
    const float yy = y * y2, yz = y * z2, zz = z * z2;
    const float wx = w * x2, wy = w * y2, wz = w * z2;

    // Populate the matrix in column-major order to match OpenGL
    out.m[0][0] = 1.0f - (yy + zz);
    out.m[1][0] = xy + wz;
    out.m[2][0] = xz - wy;
    out.m[3][0] = 0.0f;

    out.m[0][1] = xy - wz;
    out.m[1][1] = 1.0f - (xx + zz);
    out.m[2][1] = yz + wx;
    out.m[3][1] = 0.0f;

    out.m[0][2] = xz + wy;
    out.m[1][2] = yz - wx;
    out.m[2][2] = 1.0f - (xx + yy);
    out.m[3][2] = 0.0f;

    out.m[0][3] = 0.0f;
    out.m[1][3] = 0.0f;
    out.m[2][3] = 0.0f;
    out.m[3][3] = 1.0f;

    return out;
}

//	static Quaternion Quaternion::fromEulerAngles(float yaw, float pitch, float roll) {
static Quaternion fromEulerAngles(float yaw, float pitch, float roll) {
    // Convert angles to radians and halve them for quaternion calculation
    float cy = std::cos(yaw * 0.5f);
    float sy = std::sin(yaw * 0.5f);
    float cp = std::cos(pitch * 0.5f);
    float sp = std::sin(pitch * 0.5f);
    float cr = std::cos(roll * 0.5f);
    float sr = std::sin(roll * 0.5f);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

/**
    * @brief Creates a Quaternion from the rotation part of a 4x4 matrix.
    * @param mat The Mat4 to extract the rotation from.
    * @return A new Quaternion object representing the rotation.
    */
static Quaternion fromMat4(const Mat4& mat) {
    Quaternion q;
    const float matTrace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

    if (matTrace > 0.0f) {
        float s = 0.5f / std::sqrt(matTrace + 1.0f);
        q.w = 0.25f / s;
        q.x = (mat.m[2][1] - mat.m[1][2]) * s;
        q.y = (mat.m[0][2] - mat.m[2][0]) * s;
        q.z = (mat.m[1][0] - mat.m[0][1]) * s;
    }
    else if (mat.m[0][0] > mat.m[1][1] && mat.m[0][0] > mat.m[2][2]) {
        float s = 2.0f * std::sqrt(1.0f + mat.m[0][0] - mat.m[1][1] - mat.m[2][2]);
        q.w = (mat.m[2][1] - mat.m[1][2]) / s;
        q.x = 0.25f * s;
        q.y = (mat.m[0][1] + mat.m[1][0]) / s;
        q.z = (mat.m[0][2] + mat.m[2][0]) / s;
    }
    else if (mat.m[1][1] > mat.m[2][2]) {
        float s = 2.0f * std::sqrt(1.0f + mat.m[1][1] - mat.m[0][0] - mat.m[2][2]);
        q.w = (mat.m[0][2] - mat.m[2][0]) / s;
        q.x = (mat.m[0][1] + mat.m[1][0]) / s;
        q.y = 0.25f * s;
        q.z = (mat.m[1][2] + mat.m[2][1]) / s;
    }
    else {
        float s = 2.0f * std::sqrt(1.0f + mat.m[2][2] - mat.m[0][0] - mat.m[1][1]);
        q.w = (mat.m[1][0] - mat.m[0][1]) / s;
        q.x = (mat.m[0][2] + mat.m[2][0]) / s;
        q.y = (mat.m[1][2] + mat.m[2][1]) / s;
        q.z = 0.25f * s;
    }

    q.normalize();
    return q;
}




// ====================================================================
// --- CONVERT QUATERNION TO 4x4 MATRIX ---
// This is the key function that links the quaternion rotation to OpenGL.
// It generates a column-major matrix, as required by glUniformMatrix4fv.
// ====================================================================
inline void quaternionToMatrix(const Quaternion& q, float matrix[16]) {
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;

    // Fill the matrix in column-major order
    // Column 1
    matrix[0] = 1.0f - 2.0f * (y * y + z * z);
    matrix[1] = 2.0f * (x * y + w * z);
    matrix[2] = 2.0f * (x * z - w * y);
    matrix[3] = 0.0f;

    // Column 2
    matrix[4] = 2.0f * (x * y - w * z);
    matrix[5] = 1.0f - 2.0f * (x * x + z * z);
    matrix[6] = 2.0f * (y * z + w * x);
    matrix[7] = 0.0f;

    // Column 3
    matrix[8] = 2.0f * (x * z + w * y);
    matrix[9] = 2.0f * (y * z - w * x);
    matrix[10] = 1.0f - 2.0f * (x * x + y * y);
    matrix[11] = 0.0f;

    // Column 4
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}


// ====================================================================
// --- QUATERNION-VECTOR TRANSFORMATION ---
// This function rotates a 3D vector by a quaternion.
// The formula is v' = q * v * q_inverse
// ====================================================================
inline Vec3 transform(const Vec3& vec, const Quaternion& quat) {
    // 1. Create a pure quaternion from the Vec3 (w=0)
    Quaternion vecQuat(vec.x, vec.y, vec.z, 0.0f);

    // 2. Perform the rotation: q * v_quat * q_inverse
    Quaternion rotatedQuat = quat * vecQuat * quat.inverse();

    // 3. The result is the vector part of the new quaternion
    return Vec3(rotatedQuat.x, rotatedQuat.y, rotatedQuat.z);
}

#ifdef NAMESPACE_NEW_MATHLIB

/**
 * @namespace Math
 * @brief A basic math library for 3D graphics, inspired by WebGL and GLM.
 * Note that matrices are stored in column-major order to be compatible
 * with standard OpenGL/WebGL conventions.
 */
namespace Math {

    /**
     * @struct Vec3
     * @brief A 3-component vector.
     */
    struct MathVec3 {
        std::array<float, 3> data;

        // Constructor to create and initialize the vector.
        MathVec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : data({ x, y, z }) {}
    };

    /**
     * @struct Quat
     * @brief A 4-component quaternion.
     */
    struct Quat {
        std::array<float, 4> data;

        // Constructor to create and initialize the quaternion.
        Quat(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : data({ x, y, z, w }) {}
    };

    /**
     * @struct Mat4
     * @brief A 4x4 matrix, stored in column-major order.
     */
    struct Mat4 {
        std::array<float, 16> data;

        // Constructor to create an identity matrix.
        Mat4() : data({ 1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f }) {
        }
    };

    // --- Vec3 Functions ---

    /**
     * @brief Adds two Vec3's.
     * @param out The destination Vec3.
     * @param a The first operand.
     * @param b The second operand.
     */
    void add(MathVec3& out, const MathVec3& a, const MathVec3& b) {
        out.data[0] = a.data[0] + b.data[0];
        out.data[1] = a.data[1] + b.data[1];
        out.data[2] = a.data[2] + b.data[2];
    }

    /**
     * @brief Scales a Vec3 by a scalar number.
     * @param out The destination Vec3.
     * @param a The Vec3 to scale.
     * @param s The scalar.
     */
    void scale(MathVec3& out, const MathVec3& a, float s) {
        out.data[0] = a.data[0] * s;
        out.data[1] = a.data[1] * s;
        out.data[2] = a.data[2] * s;
    }

    /**
     * @brief Calculates the cross product of two Vec3's.
     * @param out The destination Vec3.
     * @param a The first operand.
     * @param b The second operand.
     */
    void cross(MathVec3& out, const MathVec3& a, const MathVec3& b) {
        const float ax = a.data[0], ay = a.data[1], az = a.data[2];
        const float bx = b.data[0], by = b.data[1], bz = b.data[2];
        out.data[0] = ay * bz - az * by;
        out.data[1] = az * bx - ax * bz;
        out.data[2] = ax * by - ay * bx;
    }

    /**
     * @brief Normalizes a Vec3.
     * @param out The destination Vec3.
     * @param a The Vec3 to normalize.
     */
    void normalize(MathVec3& out, const MathVec3& a) {
        float len = a.data[0] * a.data[0] + a.data[1] * a.data[1] + a.data[2] * a.data[2];
        if (len > 0.0f) {
            len = 1.0f / std::sqrt(len);
        }
        out.data[0] = a.data[0] * len;
        out.data[1] = a.data[1] * len;
        out.data[2] = a.data[2] * len;
    }

    /**
     * @brief Transforms a Vec3 by a Quat.
     * @param out The destination Vec3.
     * @param a The Vec3 to transform.
     * @param q The Quat to transform with.
     */
    void transformQuat(MathVec3& out, const MathVec3& a, const Quat& q) {
        const float qx = q.data[0], qy = q.data[1], qz = q.data[2], qw = q.data[3];
        const float x = a.data[0], y = a.data[1], z = a.data[2];

        float uvx = qy * z - qz * y;
        float uvy = qz * x - qx * z;
        float uvz = qx * y - qy * x;

        float uuvx = qy * uvz - qz * uvy;
        float uuvy = qz * uvx - qx * uvz;
        float uuvz = qx * uvy - qy * uvx;

        uvx *= 2.0f * qw; uvy *= 2.0f * qw; uvz *= 2.0f * qw;
        uuvx *= 2.0f; uuvy *= 2.0f; uuvz *= 2.0f;

        out.data[0] = x + uvx + uuvx;
        out.data[1] = y + uvy + uuvy;
        out.data[2] = z + uvz + uuvz;
    }

    // --- Quat Functions ---

    /**
     * @brief Sets a Quat from an axis and an angle.
     * @param out The destination Quat.
     * @param axis The axis to rotate around.
     * @param rad The angle in radians.
     */
    void setAxisAngle(Quat& out, const MathVec3& axis, float rad) {
        rad *= 0.5f;
        float s = std::sin(rad);
        out.data[0] = s * axis.data[0];
        out.data[1] = s * axis.data[1];
        out.data[2] = s * axis.data[2];
        out.data[3] = std::cos(rad);
    }

    /**
     * @brief Multiplies two Quat's.
     * @param out The destination Quat.
     * @param a The first operand.
     * @param b The second operand.
     */
    void multiply(Quat& out, const Quat& a, const Quat& b) {
        const float ax = a.data[0], ay = a.data[1], az = a.data[2], aw = a.data[3];
        const float bx = b.data[0], by = b.data[1], bz = b.data[2], bw = b.data[3];
        out.data[0] = ax * bw + aw * bx + ay * bz - az * by;
        out.data[1] = ay * bw + aw * by + az * bx - ax * bz;
        out.data[2] = az * bw + aw * bz + ax * by - ay * bx;
        out.data[3] = aw * bw - ax * bx - ay * by - az * bz;
    }

    /**
     * @brief Normalizes a Quat.
     * @param out The destination Quat.
     * @param a The Quat to normalize.
     */
    void normalize(Quat& out, const Quat& a) {
        float len = a.data[0] * a.data[0] + a.data[1] * a.data[1] + a.data[2] * a.data[2] + a.data[3] * a.data[3];
        if (len > 0.0f) {
            len = 1.0f / std::sqrt(len);
        }
        out.data[0] = a.data[0] * len;
        out.data[1] = a.data[1] * len;
        out.data[2] = a.data[2] * len;
        out.data[3] = a.data[3] * len;
    }

    // --- Mat4 Functions ---

    /**
     * @brief Creates a perspective projection matrix.
     * @param out The destination Mat4.
     * @param fovy The field of view angle in radians.
     * @param aspect The aspect ratio.
     * @param near The near clipping plane.
     * @param far The far clipping plane.
     */
    void perspective(Mat4& out, float fovy, float aspect, float near, float far) {
        const float f = 1.0f / std::tan(fovy / 2.0f);

        out.data[0] = f / aspect;
        out.data[1] = 0.0f;
        out.data[2] = 0.0f;
        out.data[3] = 0.0f;

        out.data[4] = 0.0f;
        out.data[5] = f;
        out.data[6] = 0.0f;
        out.data[7] = 0.0f;

        out.data[8] = 0.0f;
        out.data[9] = 0.0f;
        out.data[11] = -1.0f;
        out.data[15] = 0.0f;

        if (far != std::numeric_limits<float>::infinity()) {
            const float nf = 1.0f / (near - far);
            out.data[10] = (far + near) * nf;
            out.data[14] = 2.0f * far * near * nf;
        }
        else {
            out.data[10] = -1.0f;
            out.data[14] = -2.0f * near;
        }
    }

    /**
     * @brief Creates a rotation matrix from a Quat.
     * @param out The destination Mat4.
     * @param q The Quat to convert.
     */
    void fromQuat(Mat4& out, const Quat& q) {
        const float x = q.data[0], y = q.data[1], z = q.data[2], w = q.data[3];
        const float x2 = x + x, y2 = y + y, z2 = z + z;
        const float xx = x * x2, xy = x * y2, xz = x * z2;
        const float yy = y * y2, yz = y * z2, zz = z * z2;
        const float wx = w * x2, wy = w * y2, wz = w * z2;

        out.data[0] = 1.0f - (yy + zz);
        out.data[1] = xy + wz;
        out.data[2] = xz - wy;
        out.data[3] = 0.0f;

        out.data[4] = xy - wz;
        out.data[5] = 1.0f - (xx + zz);
        out.data[6] = yz + wx;
        out.data[7] = 0.0f;

        out.data[8] = xz + wy;
        out.data[9] = yz - wx;
        out.data[10] = 1.0f - (xx + yy);
        out.data[11] = 0.0f;

        out.data[12] = 0.0f;
        out.data[13] = 0.0f;
        out.data[14] = 0.0f;
        out.data[15] = 1.0f;
    }

    /**
     * @brief Translates a Mat4 by a Vec3.
     * @param out The destination Mat4.
     * @param a The Mat4 to translate.
     * @param v The Vec3 to translate by.
     */
    void translate(Mat4& out, const Mat4& a, const MathVec3& v) {
        const float x = v.data[0], y = v.data[1], z = v.data[2];

        // Copy a to out first
        out.data = a.data;

        out.data[12] = a.data[12] + a.data[0] * x + a.data[4] * y + a.data[8] * z;
        out.data[13] = a.data[13] + a.data[1] * x + a.data[5] * y + a.data[9] * z;
        out.data[14] = a.data[14] + a.data[2] * x + a.data[6] * y + a.data[10] * z;
        out.data[15] = a.data[15] + a.data[3] * x + a.data[7] * y + a.data[11] * z;
    }

    /**
     * @brief Multiplies two Mat4's.
     * @param out The destination Mat4.
     * @param a The first operand.
     * @param b The second operand.
     */
    void multiply(Mat4& out, const Mat4& a, const Mat4& b) {
        const float a00 = a.data[0], a01 = a.data[1], a02 = a.data[2], a03 = a.data[3];
        const float a10 = a.data[4], a11 = a.data[5], a12 = a.data[6], a13 = a.data[7];
        const float a20 = a.data[8], a21 = a.data[9], a22 = a.data[10], a23 = a.data[11];
        const float a30 = a.data[12], a31 = a.data[13], a32 = a.data[14], a33 = a.data[15];

        float b0, b1, b2, b3;

        b0 = b.data[0]; b1 = b.data[1]; b2 = b.data[2]; b3 = b.data[3];
        out.data[0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
        out.data[1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
        out.data[2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
        out.data[3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

        b0 = b.data[4]; b1 = b.data[5]; b2 = b.data[6]; b3 = b.data[7];
        out.data[4] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
        out.data[5] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
        out.data[6] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
        out.data[7] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

        b0 = b.data[8]; b1 = b.data[9]; b2 = b.data[10]; b3 = b.data[11];
        out.data[8] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
        out.data[9] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
        out.data[10] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
        out.data[11] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

        b0 = b.data[12]; b1 = b.data[13]; b2 = b.data[14]; b3 = b.data[15];
        out.data[12] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
        out.data[13] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
        out.data[14] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
        out.data[15] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
    }

} // namespace Math

#endif

/*

// ====================================================================
// --- A SIMPLE QUATERNION CLASS ---
// This class is essential for handling rotations without gimbal lock.
// It stores a rotation as a 4D vector (x, y, z, w).
// ====================================================================
struct Quaternion {
    float x, y, z, w;

    // Default constructor (identity quaternion)
    Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

    // Constructor with values
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    // Create a quaternion from an axis and an angle
    static Quaternion fromAxisAngle(const Vec3& axis, float angleRad) {
        float halfAngle = angleRad * 0.5f;
        float s = std::sin(halfAngle);
        float c = std::cos(halfAngle);
        Vec3 nAxis = axis.normalize();
        return Quaternion(nAxis.x * s, nAxis.y * s, nAxis.z * s, c);
    }

    // Quaternion multiplication
    // The order is important: q1 * q2 applies q2 first, then q1.
    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w,
                w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    // Normalize the quaternion
    void normalize() {
        float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
        if (magnitude > 0.0f) {
            float invMag = 1.0f / magnitude;
            x *= invMag;
            y *= invMag;
            z *= invMag;
            w *= invMag;
        }
    }
};
*/

#endif //GPS_GAME1_GOSHA_MATH3_H
