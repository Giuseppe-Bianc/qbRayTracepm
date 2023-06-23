#pragma once
#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace qbRT {
    class Cone : public ObjectBase {
    public:
        // Default constructor.
        Cone() = default;

        // Override the destructor.
        virtual ~Cone() override = default;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) override;
    };
}  // namespace qbRT
