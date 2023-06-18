#include "scene.hpp"

bool qbRT::Scene::Render(qbImage &outputImage) {
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();
    for(int x = 0; x < xSize; x++) {
        double r = (C_D(x) / w) * 255.0;
        for(int y = 0; y < ySize; y++) {
            double g = (C_D(y) / h) * 255.0;
            outputImage.SetPixel(x, y, r, g, 0.0);
        }
    }
    return true;
}
