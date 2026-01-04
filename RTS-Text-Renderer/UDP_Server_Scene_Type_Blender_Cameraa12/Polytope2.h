
#ifndef PHYSICS_POLYTOPE2
#define PHYSICS_POLYTOPE2

#if defined(_WIN32) || defined(_WIN64)_

#pragma once
#endif

#include <vector>
#include <cstdint> // For int32

// --- Assumed Type Definitions ---
// In a real codebase, these would be defined globally or in a math namespace.
using float32 = float;
using int32 = std::int32_t;

struct Vector3 {
    float32 x, y, z;
    // Assume necessary constructors, operators, and methods exist
    // e.g., Vector3(x, y, z)
    // ...
};

// =======================================================
// Polytope2 Definition
// =======================================================

/**
 * @brief Represents a 2D convex polygon (Polytope) defined by its vertices.
 * * Assumes all points lie on the Z=0 plane.
 * Assumes vertices are stored in a consistent winding order (e.g., anti-clockwise).
 */
struct Polytope2
{
    // The number of vertices/points in the polygon.
    // This directly matches the 'mnNumPoints' used in the original C code.
    int32 mnNumPoints;

    // Dynamic storage for the vertices. 
    // Uses Vector3 (x, y, z) but assumes z is near zero.
    std::vector<Vector3> m_Vertices;

    // Default Constructor
    Polytope2() : mnNumPoints(0) {}

    // Constructor for initialization
    Polytope2(const std::vector<Vector3>& points)
        : m_Vertices(points)
    {
        mnNumPoints = static_cast<int32>(m_Vertices.size());
        // assert(mnNumPoints >= 3); // Validation check
    }

    /**
     * @brief Gets the vertex at the specified index.
     * @param index The zero-based index of the vertex.
     * @return A constant reference to the Vector3 vertex position.
     */
    const Vector3& GetPoint(int32 index) const
    {
        // Simple bounds check (assertion is good practice here)
        // assert(index >= 0 && index < mnNumPoints && "Index out of bounds in Polytope2::GetPoint");
        return m_Vertices[index];
    }

    /**
     * @brief Adds a vertex to the polygon.
     * @param point The Vector3 position of the vertex (z should be 0).
     */
    void AddPoint(const Vector3& point)
    {
        m_Vertices.push_back(point);
        mnNumPoints = static_cast<int32>(m_Vertices.size());
    }

    // Optional: Getter for the entire vertex array (useful for rendering/iterating)
    const std::vector<Vector3>& GetVertices() const
    {
        return m_Vertices;
    }
};

//Based on the provided collision code, the Polytope2 class or struct must primarily store a collection of 2D vertices and provide a way to access them by index, along with a count of those vertices.The collision logic assumes the vertices are stored in a consistent order(e.g., counter - clockwise) to define a convex shape.

//Since the original code uses the functions GetPoint(i) and mnNumPoints, here is a plausible C++ implementation using a std::vector to store the points dynamically.

//C++ Polytope2 Structure
//C++

#include <vector>
#include <cstdint> // For int32

// --- Assumed Type Definitions ---
// In a real codebase, these would be defined globally or in a math namespace.
using float32 = float;
using int32 = std::int32_t;

struct Vector3 {
    float32 x, y, z;
    // Assume necessary constructors, operators, and methods exist
    // e.g., Vector3(x, y, z)
    // ...
};

// =======================================================
// Polytope2 Definition
// =======================================================

/**
 * @brief Represents a 2D convex polygon (Polytope) defined by its vertices.
 * * Assumes all points lie on the Z=0 plane.
 * Assumes vertices are stored in a consistent winding order (e.g., anti-clockwise).
 */
struct Polytope2
{
    // The number of vertices/points in the polygon.
    // This directly matches the 'mnNumPoints' used in the original C code.
    int32 mnNumPoints;

    // Dynamic storage for the vertices. 
    // Uses Vector3 (x, y, z) but assumes z is near zero.
    std::vector<Vector3> m_Vertices;

    // Default Constructor
    Polytope2() : mnNumPoints(0) {}

    // Constructor for initialization
    Polytope2(const std::vector<Vector3>& points)
        : m_Vertices(points)
    {
        mnNumPoints = static_cast<int32>(m_Vertices.size());
        // assert(mnNumPoints >= 3); // Validation check
    }

    /**
     * @brief Gets the vertex at the specified index.
     * @param index The zero-based index of the vertex.
     * @return A constant reference to the Vector3 vertex position.
     */
    const Vector3& GetPoint(int32 index) const
    {
        // Simple bounds check (assertion is good practice here)
        // assert(index >= 0 && index < mnNumPoints && "Index out of bounds in Polytope2::GetPoint");
        return m_Vertices[index];
    }

    /**
     * @brief Adds a vertex to the polygon.
     * @param point The Vector3 position of the vertex (z should be 0).
     */
    void AddPoint(const Vector3& point)
    {
        m_Vertices.push_back(point);
        mnNumPoints = static_cast<int32>(m_Vertices.size());
    }

    // Optional: Getter for the entire vertex array (useful for rendering/iterating)
    const std::vector<Vector3>& GetVertices() const
    {
        return m_Vertices;
    }
};
/*
Usage Example
C++

// Example: Creating a simple square in the X-Y plane
std::vector<Vector3> squarePoints = {
    {0.0f, 0.0f, 0.0f},  // V0
    {10.0f, 0.0f, 0.0f}, // V1
    {10.0f, 10.0f, 0.0f},// V2
    {0.0f, 10.0f, 0.0f}  // V3
};

Polytope2 Square(squarePoints);

// Accessing properties as seen in the original collision code
// int32 numEdges = Square.mnNumPoints; // Value will be 4
// const Vector3& v0 = Square.GetPoint(0);
// const Vector3& v1 = Square.GetPoint(1);
*/




#endif