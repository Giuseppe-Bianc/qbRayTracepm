#include "checker.hpp"

// Constructor / destructor.
qbRT::Texture::Checker::Checker() : m_color1{{1.0, 1.0, 1.0, 1.0}}, m_color2{{0.2, 0.2, 0.2, 1.0}} {}

// Function to return the color.
qbVector<double> qbRT::Texture::Checker::GetColor(const qbVector<double> &uvCoords) {
    // Apply the local transform to the (u,v) coordinates.
    qbVector<double> inputLoc = uvCoords;
    qbVector<double> newLoc = ApplyTransform(inputLoc);
    double newU = newLoc.GetElement(0);
    double newV = newLoc.GetElement(1);

    qbVector<double> localColor{4};
    int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));

    if((check % 2) == 0) {
        localColor = m_color1;
    } else {
        localColor = m_color2;
    }

    return localColor;
}

// Function to set the colors.
void qbRT::Texture::Checker::SetColor(const qbVector<double> &inputColor1, const qbVector<double> &inputColor2) {
    m_color1 = inputColor1;
    m_color2 = inputColor2;
}
