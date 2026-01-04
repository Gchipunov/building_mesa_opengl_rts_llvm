#include <vector>

// https://www.youtube.com/watch?v=DZRn_jNZjbw Building a PhyX like Mathlibrary and Physics System on server

// https://jakubtomsu.github.io/posts/input_in_fixed_timestep/

// https://www.gafferongames.com/post/fix_your_timestep/#:~:text=The%20simplest%20way%20to%20step%20forward%20is%20with,dt%3B%20In%20many%20ways%20this%20code%20is%20ideal.

// https://zhangmenghe.github.io/cse291d-PhysicsSimulation.html

// https://www.scribd.com/document/819113962/CSE291-13-CollisionDetection

// https://cseweb.ucsd.edu/classes/sp19/cse291-d/Files/CSE291_13_CollisionDetection.pdf

#include <glm/glm.hpp>

#include "UDPClient_update-AABB-Cubes.h"

#include "UDPClient_update_data_Cubes.h"


#include <cmath> // For std::sqrt, std::pow, etc.


// https://zhangmenghe.github.io/cse291d-PhysicsSimulation.html
// https://zhangmenghe.github.io/cse291d-PhysicsSimulation.html
// https://www.scribd.com/document/819113962/CSE291-13-CollisionDetection?v=0.757
// https://cseweb.ucsd.edu/classes/sp19/cse291-d/Files/CSE291_13_CollisionDetection.pdf
// https://cseweb.ucsd.edu/classes/sp19/cse291-d/Files/CSE291_13_CollisionDetection.pdf
// D:\Books\GPU_Gems_code\GPU Gems code
// https://developer.nvidia.com/gpugems/gpugems3/foreword
// https://www.raspberrypi.com/documentation/computers/linux_kernel.html


// Assuming glm::vec3 is used for vectors
using namespace glm;

int g_EnableClientSidePhysics = 0;

// cubes[iCubeIndex].position.x: -nan(ind), cubes[iCubeIndex].position.y: -nan(ind) , cubes[iCubeIndex].position.z: -nan(ind)
// on cubes spawning on top of each other like from KEy x will have a -nan value...
// 
// and this:
// cubes[iCubeIndex].position.x: -nan(ind), cubes[iCubeIndex].position.y: -nan(ind) , cubes[iCubeIndex].position.z: -nan(ind)


std::vector <Cube> cubes;
//std::vector <CubeGraphicsData> cubeGraphicsData;

// yaw: -90.000000, pitch: -10.000000, camera.x: -9.405636, camera.y: 0.077173, camera.z: 1.775038

// Non-member operator overloads for NetworkVector3

// Vector subtraction
NetworkVector3 operator-(const NetworkVector3& a, const NetworkVector3& b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

// Vector addition
NetworkVector3 operator+(const NetworkVector3& a, const NetworkVector3& b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

// Vector-scalar multiplication
NetworkVector3 operator*(const NetworkVector3& v, float scalar) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}

// Scalar-vector multiplication
NetworkVector3 operator*(float scalar, const NetworkVector3& v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}

// In-place vector addition
NetworkVector3& operator+=(NetworkVector3& a, const NetworkVector3& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

// In-place vector subtraction
NetworkVector3& operator-=(NetworkVector3& a, const NetworkVector3& b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}


// Dot product
float dot(const NetworkVector3& a, const NetworkVector3& b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// Length/magnitude of a vector
float length(const NetworkVector3& v) {
    return std::sqrt(dot(v, v));
}

// Normalizes a vector to a length of 1
NetworkVector3 normalize(const NetworkVector3& v) {
    float len = length(v);
    if (len > 0) {
        return { v.x / len, v.y / len, v.z / len };
    }
    return { 0.0f, 0.0f, 0.0f }; // Return zero vector for zero-length input
}


void resolveSphereCollision(Cube& a, Cube& b) {
    // This is for a sphere-based collision model, assuming "halfSize" is the radius.
    // vec3 normal = normalize(a.position - b.position); // This is the original line, now works!
    NetworkVector3 normal = normalize(a.position - b.position);

    // float overlap = (a.halfSize + b.halfSize) - length(a.position - b.position);
    float overlap = (a.halfSize + b.halfSize) - length(a.position - b.position);

    if (overlap > 0) {
        // Separate the cubes (or spheres in this model)
        NetworkVector3 separation = normal * (overlap / 2.0f);
        a.position += separation;
        b.position -= separation;

        // Simple impulse-based resolution
        // float relativeVelocity = dot(a.velocity - b.velocity, normal);
        float relativeVelocity = dot(a.velocity - b.velocity, normal);

        if (relativeVelocity < 0) {
            // vec3 impulse = (a.velocity - b.velocity) - normal * relativeVelocity;
            NetworkVector3 impulse = (a.velocity - b.velocity) - normal * relativeVelocity;

            // a.velocity -= impulse;
            // b.velocity += impulse;
            a.velocity -= impulse;
            b.velocity += impulse;
        }
    }
}

// Check for AABB collision, shpere collisioj
bool checkAABBCollision(const Cube& a, const Cube& b) {
    return (abs(a.position.x - b.position.x) < (a.halfSize + b.halfSize)) &&
        (abs(a.position.y - b.position.y) < (a.halfSize + b.halfSize)) &&
        (abs(a.position.z - b.position.z) < (a.halfSize + b.halfSize));
}

// Resolve AABB collision
/*
void resolveAABBCollision(Cube& a, Cube& b) {
    vec3 normal = normalize(a.position - b.position);
    float overlap = (a.halfSize + b.halfSize) - length(a.position - b.position);

    if (overlap > 0) {
        // Separate the cubes
        vec3 separation = normal * (overlap / 2.0f);
        a.position += separation;
        b.position -= separation;

        // Simple impulse-based resolution
        float relativeVelocity = dot(a.velocity - b.velocity, normal);
        if (relativeVelocity < 0) {
            vec3 impulse = (a.velocity - b.velocity) - normal * relativeVelocity;
            a.velocity -= impulse;
            b.velocity += impulse;
        }
    }
}*/



void resolveAABBCollisionAABB(Cube& a, Cube& b) {
    NetworkVector3 delta = a.position - b.position;
    float overlapX = (a.halfSize + b.halfSize) - std::abs(delta.x);
    float overlapY = (a.halfSize + b.halfSize) - std::abs(delta.y);
    float overlapZ = (a.halfSize + b.halfSize) - std::abs(delta.z);

    if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0) {
        return; // No collision
    }

    NetworkVector3 separationAxis = { 0.0f, 0.0f, 0.0f };
    float minOverlap = 0.0f;

    // std::abs() and std::copysign() would be useful here
    // but we can manually handle it

    if (overlapX < overlapY && overlapX < overlapZ) {
        minOverlap = overlapX;
        separationAxis.x = (delta.x > 0) ? 1.0f : -1.0f;
    }
    else if (overlapY < overlapX && overlapY < overlapZ) {
        minOverlap = overlapY;
        separationAxis.y = (delta.y > 0) ? 1.0f : -1.0f;
    }
    else {
        minOverlap = overlapZ;
        separationAxis.z = (delta.z > 0) ? 1.0f : -1.0f;
    }

    NetworkVector3 separation = separationAxis * (minOverlap / 2.0f);
    a.position += separation;
    b.position -= separation;

    NetworkVector3 normal = separationAxis;
    NetworkVector3 relativeVelocity = a.velocity - b.velocity;
    float normalVelocity = dot(relativeVelocity, normal);

    if (normalVelocity < 0) {
        float impulseMagnitude = -1.0f * normalVelocity;
        NetworkVector3 impulse = impulseMagnitude * normal;

        a.velocity += impulse;
        b.velocity -= impulse;
    }
}


// Update all cubes
void updateCubes(std::vector<Cube>& cubes, float deltaTime)
{

    // if(updateCubes: 23 deltaTime : 2.713827)
     //fix me, after no printf and cout delta time will go down
     //temp fix, just throw away frame, little bounce physics turns into a rocket launch! for stupid deltaTime being so high!
    if (deltaTime > 1.0f)
    {
        return;

    }


    //  printf("updateCubes: %d deltaTime: %f\n\r", cubes.size(), deltaTime);

    const float gravity = -9.8f;
    const float restitution = 0.5f; // Bounciness
    const float floorZ = 0.0f;

    // Apply gravity
    for (auto& cube : cubes) {
        cube.velocity.z += gravity * deltaTime;
        cube.position += cube.velocity * deltaTime;
    }

    // Floor collision
    for (auto& cube : cubes) {
        if (cube.position.z - cube.halfSize <= floorZ) {
            cube.position.z = floorZ + cube.halfSize;
            cube.velocity.z *= -restitution; // Reverse velocity with restitution
            if (abs(cube.velocity.z) < 0.1f) {
                cube.velocity.z = 0.0f; // Stop small bounces
            }
        }
    }

    // Cube-to-cube collision
    for (size_t i = 0; i < cubes.size(); ++i) {
        for (size_t j = i + 1; j < cubes.size(); ++j) {
            if (checkAABBCollision(cubes[i], cubes[j]) && i != j) {
                //    resolveAABBCollision(cubes[i], cubes[j]);
                resolveSphereCollision(cubes[i], cubes[j]);
                //    resolveAABBCollisionAABB(cubes[i], cubes[j]);
                    //  printf("resolveAABBCollision(cubes[i], cubes[j]);");

            }
        }
    }
}