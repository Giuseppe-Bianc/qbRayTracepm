#pragma once

#include "texturebase.hpp"

namespace qbRT::Texture {
    class Flat : public TextureBase {
    public:
        // Constructor / destructor.
        Flat();
        virtual ~Flat() override = default;

        // Function to return the color.
        virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;

        // Function to set the color.
        void SetColor(const qbVector<double> &inputColor);

    private:
        qbVector<double> m_color{4};
    };
}  // namespace qbRT::Texture
