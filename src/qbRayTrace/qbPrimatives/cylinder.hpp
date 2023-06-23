#pragma once

#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace qbRT {
    class Cylinder : public ObjectBase {
    public:
        // Default constructor.
        Cylinder() = default;

        // Override the destructor.
        virtual ~Cylinder() override = default;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) override;
    };
}  // namespace qbRT
