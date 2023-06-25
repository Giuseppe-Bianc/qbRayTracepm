#pragma once
#include "../qbPrimatives/box.hpp"
#include "../qbPrimatives/objectbase.hpp"
#include "sdfunc.hpp"

namespace qbRT::RM {
    class RayMarchBase : public ObjectBase {
    public:
        // Default constructor.
        RayMarchBase() = default;

        // Destructor.
        virtual ~RayMarchBase() override = default;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal,
                                      qbVector<double> &localColor) override;

        // Function to set the object function.
        void SetObjectFcn(std::function<double(qbVector<double> *, qbVector<double> *)> objectFcn);

        // Function to evaluate the Signed Distance Function (SDF) at the given coordinates.
        double EvaluateSDF(qbVector<double> *location, qbVector<double> *parms);

    public:
        // Bounding box.
        qbRT::Box m_boundingBox = qbRT::Box();

        // Parameters.
        qbVector<double> m_parms{3};

    private:
        // Pointer to object function.
        std::function<double(qbVector<double> *, qbVector<double> *)> m_objectFcn;

        bool m_haveObjectFcn = false;
        double m_epsilon = 1e-3;
        int m_maxSteps = 100;

        const double m_h = 0.001;
        qbVector<double> m_xDisp{{m_h, 0.0, 0.0}};
        qbVector<double> m_yDisp{{0.0, m_h, 0.0}};
        qbVector<double> m_zDisp{{0.0, 0.0, m_h}};
    };
}  // namespace qbRT::RM
