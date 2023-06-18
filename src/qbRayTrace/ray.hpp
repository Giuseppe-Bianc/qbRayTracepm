#pragma once
#include "../headers.h"
#include "./qbLinAlg/qbVector.h"

namespace qbRT {
    class Ray {
    public:
        Ray();
        Ray(const qbVector<double> &point1, const qbVector<double> &point2);

        inline qbVector<double> GetPoint1() const { return m_point1; }
        inline qbVector<double> GetPoint2() const { return m_point2; }

    public:
        qbVector<double> m_point1{3};
        qbVector<double> m_point2{3};
        qbVector<double> m_lab{3};
    };
}  // namespace qbRT
