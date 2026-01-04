
#ifndef PHYSICS_COLLISION_UTILITY
#define PHYSICS_COLLISION_UTILITY

#if defined(_WIN32) || defined(_WIN64)_

#pragma once
#endif

/*
#include "Polytope2.h"

// Finds the earliest time t in [0, 1] that the moving sphere (with vRelativeVelocity)
// hits the static line segment (vA to vB).
// Returns true on impact, and sets fTOI to the time.
bool SweptSphereToSegment(
    const Vector3& vA,
    const Vector3& vB,
    const BoundingSphere& Sphere,
    const Vector3& vRelativeVelocity,
    float32& fTOI,
    Vector3& vContactNormal
);;


class CollisionUtility {
public:
    CollisionUtility();
    ~CollisionUtility();

    bool SpherePolytope_Static(const BoundingSphere& Sphere, const Polytope2& Polygon);
    bool SpherePolytope_Dynamic(
        const BoundingSphere& Sphere,
        const Polytope2& Polygon,
        const Vector3& vSphereVelocity,
        float32& fTimeOfImpact,
        Vector3& vContactNormal);


};
*/
#endif