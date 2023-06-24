#pragma once
#include "../../headers.h"
#include "../gtfm.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"

namespace qbRT {
    /* Forward-declare the material base class. This will be
        overriden later. */
    class MaterialBase;

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

        // Function to assign a material.
        bool AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial);

        // Public member variables.
    public:
        // The base colour of the object.
        qbVector<double> m_baseColor{3};

        // The geometric transform applied to the object.
        qbRT::GTform m_transformMatrix;

        // A reference to the material assigned to this object.
        std::shared_ptr<qbRT::MaterialBase> m_pMaterial;

        // A flag to indicate whether this object has a material or not.
        bool m_hasMaterial = false;

        // Store the (u,v) coordinates from a detected intersection.
        qbVector<double> m_uvCoords{2};
    };
}  // namespace qbRT
