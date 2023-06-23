#include "pointlight.hpp"

// Default constructor.
qbRT::PointLight::PointLight() {
    m_color = qbVector<double>{{1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

// Function to compute illumination.
bool qbRT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                           const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                           const std::shared_ptr<qbRT::ObjectBase> &currentObject, qbVector<double> &color,
                                           double &intensity) {
    // Construct a vector pointing from the intersection point to the light.
    qbVector<double> lightDir = (m_location - intPoint).Normalized();

    // Compute a starting point.
    qbVector<double> startPoint = intPoint;

    // Construct a ray from the point of intersection to the light.
    qbRT::Ray lightRay(startPoint, startPoint + lightDir);

    /* Check for intersections with all of the objects
        in the scene, except for the current one. */
    qbVector<double> poi{3};
    qbVector<double> poiNormal{3};
    qbVector<double> poiColor{3};
    bool validInt = false;
    for(const auto &sceneObject : objectList) {
        if(sceneObject != currentObject) {
            validInt = sceneObject->TestIntersection(lightRay, poi, poiNormal, poiColor);
        }

        /* If we have an intersection, then there is no point checking further
            so we can break out of the loop. In other words, this object is
            blocking light from this light source. */
        if(validInt)
            break;
    }

    /* Only continue to compute illumination if the light ray didn't
        intersect with any objects in the scene. Ie. no objects are
        casting a shadow from this light source. */
    if(!validInt) {
        // Compute the angle between the local normal and the light ray.
        // Note that we assume that localNormal is a unit vector.
        double angle = std::acos(qbVector<double>::dot(localNormal, lightDir));

        // If the normal is pointing away from the light, then we have no illumination.
        if(angle > halfPi) {
            // No illumination.
            color = m_color;
            intensity = 0.0;
            return false;
        } else {
            // We do have illumination.
            color = m_color;
            intensity = m_intensity * (1.0 - (angle / halfPi));
            return true;
        }
    } else {
        // Shadow, so no illumination.
        color = m_color;
        intensity = 0.0;
        return false;
    }
}
