#pragma once
#include "../headers.h"
class qbImage {
public:
    // The constructor.
    explicit qbImage() = default;

    // The destructor.
    ~qbImage();

    // Function to initialise.
    void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

    // Function to set the colour of a pixel.
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);

    // Function to return the image for display.
    void Display();

    // Functions to return the dimensions of the image.
    inline int GetXSize() const { return m_xSize; }
    inline int GetYSize() const { return m_ySize; }

private:
    [[nodiscard]] Uint32 ConvertColor(const double red, const double green, const double blue) const;
    void InitTexture();
    void ComputeMaxValues();

private:
    // Arrays to store image data.
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    // Store the dimensions of the image.
    int m_xSize = 0;
    int m_ySize = 0;

    // Store the maximum values.
    double m_maxRed;
    double m_maxGreen;
    double m_maxBlue;
    double m_overallMax;

    // SDL2 stuff.
    SDL_Renderer *m_pRenderer{nullptr};
    SDL_Texture *m_pTexture{nullptr};
};
