#pragma once
#include "raymarchbase.hpp"

namespace qbRT::RM {
    class Torus : public RayMarchBase {
    public:
        // Constructor.
        Torus();

        // Destructor.
        virtual ~Torus() override = default;

        // Function to set the radii.
        void SetRadii(double r1, double r2);

    private:
        // Private object function.
        double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);

        // Function to update the bounding box.
        void UpdateBounds();

    private:
        // Radii.
        double m_r1 = 1.0;
        double m_r2 = 0.25;
    };
}  // namespace qbRT::RM
