#pragma once
#include "../Timer.h"
#include "../headers.h"
#include "camera.hpp"
#include "objsphere.hpp"
#include "qbImage.hpp"

namespace qbRT {
    class Scene {
    public:
        // The default constructor.
        Scene();

        // Function to perform the rendering.
        bool Render(qbImage &outputImage);

        // Private functions.
    private:
        // Private members.
    private:
        // The camera that we will use.
        qbRT::Camera m_camera;

        // A unit sphere on the origin, for testing.
        qbRT::ObjSphere m_testSphere;
    };
}  // namespace qbRT
