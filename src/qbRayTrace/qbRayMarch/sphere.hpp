#pragma once

#include "raymarchbase.hpp"

namespace qbRT::RM {
    class Sphere : public RayMarchBase {
    public:
        // Constructor.
        Sphere();

        // Destructor.
        virtual ~Sphere() override = default;

    private:
        // Private object function.
        double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);
    };
}  // namespace qbRT::RM
