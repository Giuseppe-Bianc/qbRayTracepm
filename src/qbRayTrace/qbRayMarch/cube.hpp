#pragma once

#include "raymarchbase.hpp"

namespace qbRT::RM {
    class Cube : public RayMarchBase {
    public:
        // Constructor.
        Cube();

        // Destructor.
        virtual ~Cube() override = default;

    private:
        // Private object function.
        double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);
    };
}  // namespace qbRT::RM
