#pragma once
#include "../qbLinAlg/qbVector.h"

namespace qbRT::RM::SDF {
    double Sphere(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
    double Torus(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
    double Box(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
}  // namespace qbRT::RM::SDF
