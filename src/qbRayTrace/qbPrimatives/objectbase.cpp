#include "objectbase.hpp"

static constexpr double EPSILON = 1e-21;

// Function to test for intersections.
bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                        qbVector<double> &localColor) {
    return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix) { m_transformMatrix = transformMatrix; }

// Function to test whether two floating-point numbers are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2) const { return fabs(f1 - f2) < EPSILON; }