#pragma once
#include "../headers.h"
class qbImage {
public:
    // Constructor.
    /* Note that we don't actually have to declare a default constructor. As we have no other constructors,
        the compiler would take of this for us. However, we later went on to define another constructor, we would
        also need to manually define the default constructor, so I always think it makes sense to just do it. */
    constexpr explicit qbImage() = default;

    // Destructor.
    ~qbImage();

    // Function to initialize.
    void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

    // Function to set pixels.
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);

    // Function to return the image for display.
    void Display();
    inline int GetXSize() const { return m_xSize; }
    inline int GetYSize() const { return m_ySize; }

private:
    Uint32 ConvertColor(const double red, const double green, const double blue) const;
    void InitTexture();

private:
    // Arrays to store image data.
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    // And store the size of the image.
    int m_xSize = 0;
    int m_ySize = 0;

    // SDL2 stuff.
    SDL_Renderer *m_pRenderer{nullptr};
    SDL_Texture *m_pTexture{nullptr};
};
