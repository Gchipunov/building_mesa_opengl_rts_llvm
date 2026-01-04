#include "CollisionUtility.h"

/*
#include <assert.h>
//------------------------------------------------
// This function assumes convexity, divide concave polygons into convex components then test each separately
// Assumes edges of polytope have not degenereted into single points
// Assumes consistent winding other order for the vertices (anti clock-wise)
// Assumes at least 3 edges (triangle)
// Assumes both sphere and polygon points are at 0 on z-axis, x,y,z order
bool
CollisionUtility::SpherePolytope_Static(const BoundingSphere& Sphere, const Polytope2& Polygon)
{

    // check some assumptions
    assert(fabsf(Sphere.GetPosition().z) < 1e-4f && "Sphere Z must be at zero or near enough for 2D polygon test in CollisionUtility::SpherePolytope_Static");
    assert(Polygon.mnNumPoints > 2 && "Polygon is expected to have at least 3 edges in CollisionUtility::SpherePolytone_Static");

    // Check if any of the vertices of the polygon are in the sphere
    float32 fRadiusSqrd = MathUtility::Square(Sphere.GetRadius());
    Vector3 vSpherePosition = Sphere.GetPosition();
    Vector3 vVertexPosition;
    Vector3 vDistVec;
    for (int32 i = 0; i < Polygon.mnNumPoints; ++i)
    {
        vVertexPosition = Polygon.GetPoint(i);
        assert(fabsf(vVertexPosition.z) < 1e-4f && "Polygon's vertices Z must be at zero for CollisionUtility::SpherePolytone_Static");

        vDistVec = vVertexPosition - vSpherePosition;
        if (vDistVec.Dot(vDistVec) <= fRadiusSqrd)
            return true;
    }

    // Check if sphere is intersecting an edge of the polygon
    Vector3 vIntersect;
    float32 fTime = 0.0f;
    int32 nNextPointIndex = 0;

    // Iterate over each edge formed by adjacent points
    for (int32 nPointIndex = 0; nPointIndex < Polygon.mnNumPoints; ++nPointIndex) // number of point is equal to number of edges
    {
        nNextPointIndex = (nPointIndex == Polygon.mnNumPoints - 1) ? 0 : nPointIndex + 1; // wrap around if at end

        if (IsLineSegmentIntersectingSphere(Polygon.GetPoint(nPointIndex), Polygon.GetPoint(nNextPointIndex), Sphere, fTime, vIntersect));
        return true;


    }
    // Check if center of sphere is inside the 2D polygon's bounds
    return IsPointInConvexPolygon(vSpherePosition, Polygon);
}



bool
CollisionUtility::SpherePolytope_Dynamic(
    const BoundingSphere& Sphere,
    const Polytope2& Polygon,
    const Vector3& vSphereVelocity,
    float32& fTimeOfImpact,
    Vector3& vContactNormal)
{
    fTimeOfImpact = 1.0f; // Initialize to the end of the time step (no impact)
    Vector3 vRelativeVelocity = vSphereVelocity; // Assuming Polygon is static
    Vector3 vCurrentNormal;
    float32 fCurrentTOI;

    // --- A. Swept Sphere vs. Vertices (Collision with Point) ---
    // A vertex is a degenerate edge. This is a sphere-to-sphere collision
    // where the 'target sphere' has a radius of zero.
    // This often yields a simple quadratic equation.
    for (int32 i = 0; i < Polygon.mnNumPoints; ++i)
    {
        // Check collision between the moving sphere and the static point (vertex)
        if (SweptSphereToPoint(Sphere, Polygon.GetPoint(i), vRelativeVelocity, fCurrentTOI, vCurrentNormal))
        {
            if (fCurrentTOI < fTimeOfImpact)
            {
                fTimeOfImpact = fCurrentTOI;
                vContactNormal = vCurrentNormal;
            }
        }
    }

    // --- B. Swept Sphere vs. Edges (Collision with Segment) ---
    // This is the check against the sides/faces.
    for (int32 nPointIndex = 0; nPointIndex < Polygon.mnNumPoints; ++nPointIndex)
    {
        int32 nNextPointIndex = (nPointIndex == Polygon.mnNumPoints - 1) ? 0 : nPointIndex + 1;

        if (SweptSphereToSegment(
            Polygon.GetPoint(nPointIndex),
            Polygon.GetPoint(nNextPointIndex),
            Sphere,
            vRelativeVelocity,
            fCurrentTOI,
            vCurrentNormal))
        {
            if (fCurrentTOI < fTimeOfImpact)
            {
                fTimeOfImpact = fCurrentTOI;
                vContactNormal = vCurrentNormal;
            }
        }
    }

    // If fTimeOfImpact < 1.0f, a collision occurred.
    return (fTimeOfImpact < 1.0f);
}


//------------------------------------------
//------------------------------------------
//------------------------------------------
//------------------------------------------
//------------------------------------------


#include <cmath>
#include <algorithm> // For std::min

// --- Placeholder/Assumed Utility Functions and Types ---
// In a real engine, these would be defined in your MathUtility or Vector3 class.
// For demonstration, we assume they exist:
using float32 = float;

// Assuming Vector3 has: x, y, z members; operator-, operator+; Dot()
struct Vector3 {
    float32 x, y, z;
    // ...
    Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
    Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    Vector3 operator*(float32 s) const { return { x * s, y * s, z * s }; }
    float32 Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
    float32 LengthSq() const { return Dot(*this); }
    // Add Normalize() in a real implementation
    // ...
};

struct BoundingSphere {
    Vector3 GetPosition() const; // Assumed function
    float32 GetRadius() const;   // Assumed function
    // ...
};

namespace MathUtility {
    inline float32 Square(float32 v) { return v * v; }
    inline float32 Clamp(float32 v, float32 min, float32 max) {
        return std::max(min, std::min(v, max));
    }
}

// --- Implementation ---

// Helper function to find the closest point (p) on the segment (a to b)
// to the point (c). Returns the parameter t in [0, 1] for p = a + t * (b - a).
float32 ClosestPointOnSegmentToPointParam(
    const Vector3& vA,
    const Vector3& vB,
    const Vector3& vC)
{
    Vector3 vAB = vB - vA;
    Vector3 vAC = vC - vA;

    // Project vAC onto vAB
    float32 fT = vAC.Dot(vAB);

    // Check if vAB is degenerate (zero length)
    float32 fD = vAB.Dot(vAB);
    if (fD < 1e-6f) return 0.0f; // Treat as just point vA

    fT /= fD;

    // Clamp t to [0, 1] to ensure the closest point is on the segment
    return MathUtility::Clamp(fT, 0.0f, 1.0f);
}

bool SweptSphereToSegment(
    const Vector3& vA,
    const Vector3& vB,
    const BoundingSphere& Sphere,
    const Vector3& vRelativeVelocity,
    float32& fTOI,
    Vector3& vContactNormal)
{
    float32 fMinTOI = 1.0f;
    bool bHit = false;
    Vector3 vSegmentDir = vB - vA;
    Vector3 vSphereCenter = Sphere.GetPosition();
    float32 fRadius = Sphere.GetRadius();
    float32 fRadiusSqrd = MathUtility::Square(fRadius);

    // 1. Check for collision with the segment's **endpoints** (Sphere-vs-Point)
    // The sphere is moving towards a static point (vA or vB).

    // Check endpoint vA
    if (SweptSphereToPoint(vSphereCenter, vA, fRadius, vRelativeVelocity, fMinTOI, vContactNormal))
    {
        bHit = true;
    }

    // Check endpoint vB (only if it's earlier than the best TOI so far)
    Vector3 vTempNormal;
    float32 fTempTOI = fMinTOI;
    if (SweptSphereToPoint(vSphereCenter, vB, fRadius, vRelativeVelocity, fTempTOI, vTempNormal))
    {
        if (fTempTOI < fMinTOI)
        {
            fMinTOI = fTempTOI;
            vContactNormal = vTempNormal;
        }
        bHit = true;
    }

    // 2. Check for collision with the segment's **interior** (Sphere-vs-Infinite Line)
    // Find the closest approach time to the *infinite line* containing the segment.

    // Relative position and velocity vectors
    Vector3 vR = vSphereCenter - vA; // Vector from A to sphere center
    Vector3 vV = vRelativeVelocity;

    // Define the line direction (SegmentDir) as D, and velocity as V.
    // The closest point on the line to the sphere center will be P(t) = C0 + tV - R * N
    // where C0 is the initial center, N is the normalized vector perpendicular to D.

    // The distance is minimized when the vector (C0 + tV - A) is perpendicular to D.
    // (C0 + tV - A) . D = 0 -> (R + tV) . D = 0 -> R.D + t(V.D) = 0
    // We are solving for the closest approach of the *center* to the *line*.

    // Project the displacement onto the plane perpendicular to the line:
    float32 a = vV.LengthSq() - MathUtility::Square(vV.Dot(vSegmentDir) / vSegmentDir.LengthSq());
    float32 b = 2.0f * (vV.Dot(vR) - (vV.Dot(vSegmentDir) * vR.Dot(vSegmentDir)) / vSegmentDir.LengthSq());
    float32 c = vR.LengthSq() - fRadiusSqrd - MathUtility::Square(vR.Dot(vSegmentDir) / vSegmentDir.LengthSq());

    // The full quadratic equation for swept sphere vs. infinite line (Simplified for explanation):
    // a*t^2 + b*t + c = 0 (where a, b, c are derived from the geometric setup)

    // Simplified derivation for 2D/Line Segment:
    // P(t) = C0 + t * V
    // D(t) = P(t) - Q, where Q is the closest point on the infinite line to P(t).
    // The distance squared |P(t) - Q|^2 = R^2
    // We can re-express this by looking at the distance vector W = P(t) - A.
    // The perpendicular distance squared is: |W|^2 - (W . D)^2 / |D|^2 = R^2

    // Simplified variables for 2D/Line approach:
    Vector3 w = vSphereCenter - vA;
    float32 fDLenSq = vSegmentDir.LengthSq();

    // 'a', 'b', and 'c' for the quadratic equation of the closest point squared distance.
    // The variables are simplified for the closest-approach distance to the infinite line.

    // The actual distance to the *infinite line* squared:
    // dist^2(t) = |(w + t*v) x D|^2 / |D|^2. We want dist^2(t) = R^2.
    // This is computationally simpler using the geometric projection:

    Vector3 vAP = vA - vSphereCenter; // Vector from Sphere to A
    Vector3 vDir = vB - vA;
    float32 fA_quad = vDir.LengthSq(); // |D|^2

    // (P(t) - A) . D = 0 is not the right formula for TOI.
    // The correct formula is a*t^2 + b*t + c = 0 where a, b, c relate to the *squared distance* to the line.

    // a = V_perp . V_perp, b = 2 * W_perp . V_perp, c = W_perp . W_perp - R^2
    // W_perp = W - proj_D(W), V_perp = V - proj_D(V)

    float32 fDotVV = vRelativeVelocity.Dot(vRelativeVelocity);
    float32 fDotDV = vSegmentDir.Dot(vRelativeVelocity);
    float32 fDotDW = vSegmentDir.Dot(w);
    float32 fDotWW = w.Dot(w);

    // The quadratic coefficients (A, B, C) for the squared distance equation:
    float32 fA_term = fDLenSq * fDotVV - fDotDV * fDotDV;
    float32 fB_term = 2.0f * (fDLenSq * vRelativeVelocity.Dot(w) - fDotDV * fDotDW);
    float32 fC_term = fDLenSq * (fDotWW - fRadiusSqrd) - fDotDW * fDotDW;

    // Only proceed if 'a' is not near zero (i.e., velocity is not parallel to the segment)
    if (fabsf(fA_term) > 1e-6f)
    {
        // Solve the quadratic equation: A*t^2 + B*t + C = 0
        float32 fDiscriminant = fB_term * fB_term - 4.0f * fA_term * fC_term;

        if (fDiscriminant >= 0.0f)
        {
            float32 fSqrtDisc = sqrtf(fDiscriminant);
            float32 fT1 = (-fB_term - fSqrtDisc) / (2.0f * fA_term);
            float32 fT2 = (-fB_term + fSqrtDisc) / (2.0f * fA_term);

            float32 fEarliestT = std::min(fT1, fT2);

            if (fEarliestT >= 0.0f && fEarliestT <= fMinTOI)
            {
                // The time is valid. Now, check if the contact point is on the segment.
                // P_contact = C_initial + fEarliestT * V_relative
                Vector3 vContactCenter = vSphereCenter + vRelativeVelocity * fEarliestT;

                // Find the parameter 't_seg' for the closest point on the segment to P_contact
                float32 fT_seg = ClosestPointOnSegmentToPointParam(vA, vB, vContactCenter);

                if (fT_seg > 0.0f + 1e-4f && fT_seg < 1.0f - 1e-4f) // Check for interior (excluding endpoints)
                {
                    // Collision is with the interior of the segment.
                    fMinTOI = fEarliestT;
                    bHit = true;

                    // The contact point on the segment is Q = vA + fT_seg * vSegmentDir
                    Vector3 vContactPoint = vA + vSegmentDir * fT_seg;

                    // Normal is vector from Q to contact center, normalized
                    vContactNormal = vContactCenter - vContactPoint;
                    // vContactNormal.Normalize(); // Assumed Normalize() exists
                }
            }
        }
    }

    // Final check for contact time (must be in [0, 1] range)
    if (bHit && fMinTOI >= 0.0f && fMinTOI <= 1.0f)
    {
        fTOI = fMinTOI;
        // In a real implementation, you must normalize vContactNormal here.
        return true;
    }

    return false;
}

// --- Required Helper Function for Endpoint (Sphere-vs-Point) ---
// Checks moving sphere vs. static point.
bool SweptSphereToPoint(
    const Vector3& vSphereCenter,
    const Vector3& vPoint,
    float32 fRadius,
    const Vector3& vRelativeVelocity,
    float32& fTOI,
    Vector3& vContactNormal)
{
    Vector3 vDiff = vSphereCenter - vPoint;
    float32 fRadiusSqrd = MathUtility::Square(fRadius);

    // a*t^2 + b*t + c = 0
    // a = V.V
    // b = 2 * V.W (where W = vDiff)
    // c = W.W - R^2

    float32 a = vRelativeVelocity.Dot(vRelativeVelocity);
    float32 b = 2.0f * vRelativeVelocity.Dot(vDiff);
    float32 c = vDiff.Dot(vDiff) - fRadiusSqrd;

    // If the sphere is moving very slowly or is already outside
    if (fabsf(a) < 1e-6f) return false;

    float32 fDiscriminant = b * b - 4.0f * a * c;

    if (fDiscriminant < 0.0f) return false; // No real intersection

    float32 fSqrtDisc = sqrtf(fDiscriminant);
    float32 fT1 = (-b - fSqrtDisc) / (2.0f * a);
    float32 fT2 = (-b + fSqrtDisc) / (2.0f * a);

    // We only care about the earliest time of impact (t > 0)
    float32 fEarliestT = std::min(fT1, fT2);

    // If the earliest TOI is better than the current best
    if (fEarliestT >= 0.0f && fEarliestT <= 1.0f && fEarliestT < fTOI)
    {
        fTOI = fEarliestT;

        // Calculate the normal at contact
        // P_contact = C_initial + fTOI * V_relative
        Vector3 vContactCenter = vSphereCenter + vRelativeVelocity * fTOI;
        vContactNormal = vContactCenter - vPoint;
        // vContactNormal.Normalize(); // Assumed Normalize() exists

        return true;
    }

    return false;
}
*/