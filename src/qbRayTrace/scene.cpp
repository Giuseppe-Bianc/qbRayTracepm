#include "scene.hpp"

qbRT::Scene::Scene() {
    // Configure the camera.
    m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();
}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage) {
    Timer Timer{"Render"};
    // Get the dimensions of the output image.
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();
    double halfXSise = static_cast<double>(xSize) / 2.0;
    double halfYSise = static_cast<double>(ySize) / 2.0;

    // Loop over each pixel in our image.
    qbRT::Ray cameraRay;
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};
    double xFact = 1.0 / halfXSise;
    double yFact = 1.0 / halfYSise;
    double minDist = 1e6;
    double maxDist = 0.0;
    double normX = 0;
    double normY = 0;
#pragma omp parallel for
    for(auto x : std::views::iota(0, xSize)) {
        normX = (static_cast<double>(x) * xFact) - 1.0;
        for(auto y : std::views::iota(0, ySize)) {
            // Normalize the x and y coordinates.
            normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the ray for this pixel.
            m_camera.GenerateRay(C_F(normX), C_F(normY), cameraRay);

            // Test if we have a valid intersection.
            bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);

            // If we have a valid intersection, change pixel color to red.
            if(validInt) {
                // Compute the distance between the camera and the point of intersection.
                double dist = (intPoint - cameraRay.m_point1).norm();
                if(dist > maxDist)
                    maxDist = dist;

                if(dist < minDist)
                    minDist = dist;

                outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
            } else {
                outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
            }
        }
    }

    QBINFO("Minimum distance: {:.12f}", minDist);
    QBINFO("Maximum distance: {:.12f}", maxDist);

    return true;
}
