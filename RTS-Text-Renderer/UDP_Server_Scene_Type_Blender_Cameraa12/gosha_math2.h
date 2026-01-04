#ifndef COLO_GAME_GOSHA_MATH2_H
#define COLO_GAME_GOSHA_MATH2_H


#include <iostream>
#include <array>
#include <cmath> // For tan, radians (if needed for perspective, though ortho is used here)

//#include "gosha_math3.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Simple 3D Vector class.
 */
struct Vec3 {
    float x, y, z;

    Vec3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) : x(x_), y(y_), z(z_) {}
    // Method to calculate the squared length of the vector
    float lengthSquared() const {
        return x * x + y * y + z * z;
    }

    // Method to calculate the length (magnitude) of the vector
    float length() const {
        return std::sqrt(lengthSquared());
    }

    // Normalize function that returns a new normalized Vec3

    Vec3 normalize() const {
        float len = length();
        if (len > 0) {
            return Vec3(x / len, y / len, z / len);
        }
        else {
            // Handle the zero vector case to avoid division by zero.
            // A zero vector's normalization is typically defined as the zero vector itself.
            return Vec3(0.0f, 0.0f, 0.0f);
        }
    }

    // Add the unary negation operator for Vec3
    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }


    // NEW: Add the multiplication operator for Vec3 * float
    // This is defined as a member function, which means the Vec3 is the left operand.
    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // You also need the addition operator to make the line work.
    // this->position + upDir
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // You might also need the compound assignment operator +=
    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }


};

// It's also good practice to define the free function for float * Vec3,
// as the member function only handles Vec3 * float.
inline Vec3 operator*(float scalar, const Vec3& vec) {
    return vec * scalar;
}

struct Vec4 {
    float x, y, z, w;

    Vec4(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f, float w_ = 0.0f) : x(x_), y(y_), z(z_), w(w_) {}
};

//union Vec4 {
 //   struct {
 //       float x, y, z, w;
 //   };
//    float idx[4];
//};


struct  gosha_vec2 {
    float x, y, z;

    //   gosha_vec2(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) : x(x_), y(y_), z(z_) {}
    gosha_vec2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) { z = 0.0f; }
};



class Mat4 {
public:
    // Using a C-style array for direct memory layout similar to OpenGL's expectations
    // m[col][row] -> m[0] is column 0, m[0][0] is element at (0,0)
    float m[4][4];

    /**
     * @brief Constructor: Initializes an identity matrix.
     */
    Mat4() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }
    /**
         * @brief Creates and returns a new identity matrix.
         * @return A new Mat4 object initialized as an identity matrix.
         */
    static Mat4 Identity() {
        return Mat4(); // The default constructor already creates an identity matrix.
    }
    /**
     * @brief Matrix multiplication operator.
     * @param other The right-hand side matrix.
     * @return The resulting matrix.
     */
    Mat4 operator*(const Mat4& other) const {
        Mat4 result; // Starts as identity, will be overwritten
        for (int i = 0; i < 4; ++i) { // Column of result
            for (int j = 0; j < 4; ++j) { // Row of result
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) { // Summation index
                    result.m[i][j] += m[k][j] * other.m[i][k];
                }
            }
        }
        return result;
    }

    /**
     * @brief Applies a translation to the current matrix.
     * @param v The translation vector.
     * @return A new matrix with the translation applied.
     */
    Mat4 translate(const Vec3& v) const {
        Mat4 result = *this; // Start with a copy of the current matrix
        // Translation values are in the last column (column 3)
        // m[3][0] = x, m[3][1] = y, m[3][2] = z
        // The translation is applied to the existing matrix
        result.m[3][0] += v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
        result.m[3][1] += v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
        result.m[3][2] += v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
        result.m[3][3] += v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3];
        return result;
    }

    /**
     * @brief Applies a scaling to the current matrix.
     * @param v The scaling vector.
     * @return A new matrix with the scaling applied.
     */
    Mat4 scale(const Vec3& v) const {
        Mat4 result = *this;
        result.m[0][0] *= v.x; result.m[1][0] *= v.y; result.m[2][0] *= v.z;
        result.m[0][1] *= v.x; result.m[1][1] *= v.y; result.m[2][1] *= v.z;
        result.m[0][2] *= v.x; result.m[1][2] *= v.y; result.m[2][2] *= v.z;
        result.m[0][3] *= v.x; result.m[1][3] *= v.y; result.m[2][3] *= v.z;
        return result;
    }

    /**
     * @brief Creates an orthographic projection matrix.
     * @param left The left clipping plane.
     * @param right The right clipping plane.
     * @param bottom The bottom clipping plane.
     * @param top The top clipping plane.
     * @param zNear The near clipping plane.
     * @param zFar The far clipping plane.
     * @return The orthographic projection matrix.
     */
    static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
        Mat4 result; // Starts as identity
        result.m[0][0] = 2.0f / (right - left);
        result.m[1][1] = 2.0f / (top - bottom);
        result.m[2][2] = -2.0f / (zFar - zNear); // OpenGL convention
        result.m[3][0] = -(right + left) / (right - left);
        result.m[3][1] = -(top + bottom) / (top - bottom);
        result.m[3][2] = -(zFar + zNear) / (zFar - zNear);
        return result;
    }

    /**
     * @brief Creates a "look at" view matrix.
     * @param eye The position of the camera.
     * @param center The point the camera is looking at.
     * @param up The up direction of the camera.
     * @return The view matrix.
     */
    static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        // Calculate the camera's forward, right, and up vectors
        Vec3 f = { center.x - eye.x, center.y - eye.y, center.z - eye.z };
        float f_len = std::sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
        f = { f.x / f_len, f.y / f_len, f.z / f_len }; // Normalize f

        Vec3 s = { f.y * up.z - f.z * up.y, f.z * up.x - f.x * up.z, f.x * up.y - f.y * up.x }; // Cross product f x up
        float s_len = std::sqrt(s.x * s.x + s.y * s.y + s.z * s.z);
        s = { s.x / s_len, s.y / s_len, s.z / s_len }; // Normalize s

        Vec3 u = { s.y * f.z - s.z * f.y, s.z * f.x - s.x * f.z, s.x * f.y - s.y * f.x }; // Cross product s x f

        Mat4 result;
        result.m[0][0] = s.x;
        result.m[1][0] = s.y;
        result.m[2][0] = s.z;
        result.m[0][1] = u.x;
        result.m[1][1] = u.y;
        result.m[2][1] = u.z;
        result.m[0][2] = -f.x; // Negative f because OpenGL is right-handed
        result.m[1][2] = -f.y;
        result.m[2][2] = -f.z;
        result.m[3][0] = -(s.x * eye.x + s.y * eye.y + s.z * eye.z); // Dot product -s.eye
        result.m[3][1] = -(u.x * eye.x + u.y * eye.y + u.z * eye.z); // Dot product -u.eye
        result.m[3][2] = -(-f.x * eye.x + -f.y * eye.y + -f.z * eye.z); // Dot product f.eye (since f is negated)
        // result.m[3][3] remains 1.0f from identity constructor

        return result;
    }
    void add(Vec3& out, const Vec3& a, const Vec3& b) {
        //  out.data[0] = a.data[0] + b.data[0];
       //   out.data[1] = a.data[1] + b.data[1];
        //  out.data[2] = a.data[2] + b.data[2];
        out.x = a.x + b.x;
        out.y = a.y + b.y;
        out.z = a.z + b.z;

    }

    /**
   * @brief Creates a perspective projection matrix.
   * @param fovy The field of view in degrees.
   * @param aspect The aspect ratio.
   * @param zNear The near clipping plane.
   * @param zFar The far clipping plane.
   * @return The perspective projection matrix.
   */
    static Mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
        Mat4 result;
        const float tanHalfFovy = tan(fovy / 2.0f * (float)M_PI / 180.0f);

        result.m[0][0] = 1.0f / (aspect * tanHalfFovy);
        result.m[1][1] = 1.0f / tanHalfFovy;
        result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
        result.m[2][3] = -1.0f;
        result.m[3][2] = -2.0f * zFar * zNear / (zFar - zNear);

        result.m[0][1] = result.m[0][2] = result.m[0][3] = 0.0f;
        result.m[1][0] = result.m[1][2] = result.m[1][3] = 0.0f;
        result.m[2][0] = result.m[2][1] = 0.0f;
        result.m[3][0] = result.m[3][1] = result.m[3][3] = 0.0f;

        return result;
    }

    /**
    * @brief Calculates the inverse of the matrix.
    *
    * @note This function is specifically optimized for matrices that represent
    * affine transformations (translation and rotation/scaling), such as the
    * "lookAt" matrix. It will not work for perspective projection matrices.
    *
    * The inverse of a rigid body transformation matrix [R | T] is [R^T | -R^T * T].
    * Here, R is the 3x3 rotation sub-matrix, and T is the translation vector.
    *
    * @return The inverted matrix.
    */
    Mat4 inverse() const {
        Mat4 result = Mat4::Identity();

        // 1. Transpose the 3x3 rotation sub-matrix
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.m[i][j] = this->m[j][i];
            }
        }

        // 2. Calculate the new translation vector.
        // The original translation vector is the last column of the matrix.
        // It needs to be transformed by the new, transposed rotation matrix.
        float tx = this->m[3][0];
        float ty = this->m[3][1];
        float tz = this->m[3][2];

        // The new translation is -R^T * T
        result.m[3][0] = -(result.m[0][0] * tx + result.m[1][0] * ty + result.m[2][0] * tz);
        result.m[3][1] = -(result.m[0][1] * tx + result.m[1][1] * ty + result.m[2][1] * tz);
        result.m[3][2] = -(result.m[0][2] * tx + result.m[1][2] * ty + result.m[2][2] * tz);

        return result;
    }


    /**
     * @brief Returns a pointer to the first element of the matrix.
     * Useful for passing to OpenGL functions like glUniformMatrix4fv.
     * @return A float pointer to the matrix data.
     */
    const float* value_ptr() const {
        return &m[0][0];
    }

    /**
     * @brief Prints the matrix to console (for debugging).
     */
    void print() const {
        for (int j = 0; j < 4; ++j) { // Iterate rows
            for (int i = 0; i < 4; ++i) { // Iterate columns
                std::cout << m[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};


union Vector4 {
    struct {
        float x, y, z, w;
    };
    float idx[4];
};

struct Vertex {
    constexpr Vertex(const Vector4& inPosition, const Vector4& inUV) : position(inPosition),
        uv(inUV) {
    }

    Vector4 position;
    Vector4 uv;
};
// std::vector<Vertex> vertices = {
//           Vertex(Vector3{1, 1, 0}, Vector2{0, 0}), // 0
//           Vertex(Vector3{-1, 1, 0}, Vector2{1, 0}), // 1
 //          Vertex(Vector3{-1, -1, 0}, Vector2{1, 1}), // 2
//           Vertex(Vector3{1, -1, 0}, Vector2{0, 1}) // 3
//   };
//   std::vector<Index> indices = {
 //          0, 1, 2, 0, 2, 3
//   };


#endif