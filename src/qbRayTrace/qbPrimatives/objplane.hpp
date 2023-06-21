#pragma once
#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace qbRT {
    class ObjPlane : public ObjectBase {
    public:
        // Default constructor.
        ObjPlane() = default;

        // Override the destructor.
        virtual ~ObjPlane() override = default;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) override;

    private:
    };
}  // namespace qbRT
