#include "qbImage.hpp"

// The destructor.
qbImage::~qbImage() {
    if(m_pTexture != nullptr)
        SDL_DestroyTexture(m_pTexture);
}

// Function to inialize.
void qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer) {
    // Resize the image arrays.
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    // Store the dimensions.
    m_xSize = xSize;
    m_ySize = ySize;

    // Store the pointer to the renderer.
    m_pRenderer = pRenderer;

    // Initialise the texture.
    InitTexture();
}

// Function to set pixels.
void qbImage::SetPixel(const int x, const int y, const double red, const double green, const double blue) {
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

// Function to generate the display.
void qbImage::Display() {
    // Compute maximum values.
    ComputeMaxValues();

    // Allocate memory for a pixel buffer.
    std::vector<Uint32> tempPixels(m_xSize * m_ySize, 0);
    std::size_t index{};

#pragma omp parallel for
    for(int x = 0; x < m_xSize; ++x) {
        for(int y = 0; y < m_ySize; ++y) {
            const auto &r = m_rChannel[x][y];
            const auto &g = m_gChannel[x][y];
            const auto &b = m_bChannel[x][y];
            index = (y * m_xSize) + x;
            tempPixels[index] = ConvertColor(r, g, b);
        }
    }

    // Update the texture with the pixel buffer.
    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels.data(), m_xSize * sizeof(Uint32));

    // Copy the texture to the renderer.
    SDL_Rect srcRect{0, 0, m_xSize, m_ySize};
    SDL_Rect bounds;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

// Function to initialize the texture.
void qbImage::InitTexture() {
    // Delete any previously created texture.
    if(m_pTexture != nullptr)
        SDL_DestroyTexture(m_pTexture);
    // Create the texture that will store the image.
    SDL_Surface *tempSurface = SDL_CreateRGBSurfaceWithFormat(0, m_xSize, m_ySize, 32, SDL_PIXELFORMAT_RGBA32);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

// Function to convert colours to Uint32
[[nodiscard]] Uint32 qbImage::ConvertColor(const double red, const double green, const double blue) const {
    // Convert the colours to unsigned integers.
    const double invMax = 255.0 / m_overallMax;
    auto r = static_cast<unsigned char>(red * invMax);
    auto g = static_cast<unsigned char>(green * invMax);
    auto b = static_cast<unsigned char>(blue * invMax);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 pixelColor = (r << 24) | (g << 16) | (b << 8) | 255;
#else
    const Uint32 pixelColor = (255 << 24) | (r << 16) | (g << 8) | b;
#endif

    return pixelColor;
}

// Function to compute maximum values.
void qbImage::ComputeMaxValues() {
    m_maxRed = 0.0;
    m_maxGreen = 0.0;
    m_maxBlue = 0.0;
    m_overallMax = 0.0;
    for(int x = 0; x < m_xSize; ++x) {
        for(int y = 0; y < m_ySize; ++y) {
            const double &redValue = m_rChannel.at(x).at(y);
            const double &greenValue = m_gChannel.at(x).at(y);
            const double &blueValue = m_bChannel.at(x).at(y);

            m_maxRed = std::max(m_maxRed, redValue);
            m_maxGreen = std::max(m_maxGreen, greenValue);
            m_maxBlue = std::max(m_maxBlue, blueValue);

            m_overallMax = std::max({m_maxRed, m_maxGreen, m_maxBlue, m_overallMax});
        }
    }
}
