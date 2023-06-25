#include "objectbase.hpp"

static constexpr double EPSILON = 1e-21;

// Function to test for intersections.
bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                        qbVector<double> &localColor) {
    return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix) { m_transformMatrix = transformMatrix; }

qbRT::GTform qbRT::ObjectBase::GetTransformMatrix() const { return m_transformMatrix; }

// Function to assign a material.
bool qbRT::ObjectBase::AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial) {
    m_pMaterial = objectMaterial;
    m_hasMaterial = true;
    return m_hasMaterial;
}

// Function to test whether two floating-point numbers are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2) const { return std::fabs(f1 - f2) < EPSILON; }
