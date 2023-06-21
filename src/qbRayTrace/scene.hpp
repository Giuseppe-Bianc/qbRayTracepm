#pragma once
#include "../Timer.h"
#include "../headers.h"
#include "camera.hpp"
#include "objplane.hpp"
#include "objsphere.hpp"
#include "pointlight.hpp"
#include "qbImage.hpp"

namespace qbRT {
    class Scene {
    public:
        // The default constructor.
        Scene();

        // Function to perform the rendering.
        bool Render(qbImage &outputImage) const;

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
