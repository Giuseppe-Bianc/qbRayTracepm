#pragma once
#include "../headers.h"
#include "./qbLinAlg/qbVector.h"
#include "gtfm.hpp"
#include "ray.hpp"

namespace qbRT {
    class ObjectBase {
    public:
        // Constructor and destructor.
        ObjectBase() = default;
        virtual ~ObjectBase() = default;

        // Function to test for intersections.
        virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor);

        // Function to set the transform matrix.
        void SetTransformMatrix(const qbRT::GTform &transformMatrix);

        // Function to test whether two floating-point numbers are close to being equal.
        bool CloseEnough(const double f1, const double f2) const;

        // Public member variables.
    public:
        // The base colour of the object.
        qbVector<double> m_baseColor{3};

        // The geometric transform applied to the object.
        qbRT::GTform m_transformMatrix;
    };
}  // namespace qbRT
