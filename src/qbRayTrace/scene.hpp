#pragma once
#include "../headers.h"
#include "qbImage.hpp"

namespace qbRT {
    class Scene {
    public:
        constexpr Scene() = default;

        constexpr ~Scene() = default;

        bool Render(qbImage &outputImage);

    private:
    };

}  // namespace qbRT
