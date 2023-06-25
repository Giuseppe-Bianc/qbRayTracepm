#pragma once
#include "../gtfm.hpp"
#include "objectbase.hpp"

namespace qbRT {
    class Box : public ObjectBase {
    public:
        /* The default constructor.
            Note that this will define a unit sphere at the origin. */
        Box() = default;

        // Override the destructor.
        virtual ~Box() override = default;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) override;

    private:
        std::array<double, 6> t;
        std::array<double, 6> u;
        std::array<double, 6> v;
    };
}  // namespace qbRT
