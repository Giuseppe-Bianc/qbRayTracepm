#pragma once
#include "../Timer.h"
#include "../headers.h"
#include "./qbLights/pointlight.hpp"
#include "./qbPrimatives/objplane.hpp"
#include "./qbPrimatives/objsphere.hpp"
#include "camera.hpp"
#include "qbImage.hpp"

namespace qbRT {
    class Scene {
    public:
        // The default constructor.
        Scene();

        // Function to perform the rendering.
        bool Render(qbImage &outputImage) const;

        // Function to cast a ray into the scene.
        bool CastRay(const qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                     qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                     qbVector<double> &closestLocalColor) const;

        // Private functions.
    private:
        // Private members.
    private:
        // The camera that we will use.
        qbRT::Camera m_camera;

        // The list of objects in the scene.
        std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;

        // The list of lights in the scene.
        std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;
    };
}  // namespace qbRT
