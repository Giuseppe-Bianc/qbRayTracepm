#pragma once
#include "../headers.h"
#include "objectbase.hpp"

namespace qbRT {
    class ObjSphere : public ObjectBase {
    public:
        /* The default constructor.
            Note that this will define a unit sphere at the origin. */
        ObjSphere();

        // Override the destructor.
        virtual ~ObjSphere() override;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor);

    private:
    };
}  // namespace qbRT
