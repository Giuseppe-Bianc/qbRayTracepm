#include "scene.hpp"

// The constructor.
qbRT::Scene::Scene() {
    // Configure the camera.
    m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Construct a test sphere.
    m_objectList.push_back(std::make_shared<qbRT::ObjSphere>());

    // Construct a test light.
    m_lightList.push_back(std::make_shared<qbRT::PointLight>());
    m_lightList.at(0)->m_location = qbVector<double>{std::vector<double>{5.0, -10.0, 5.0}};
    m_lightList.at(0)->m_color = qbVector<double>{std::vector<double>{255.0, 255.0, 255.0}};
}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage) {
    Timer Timer{"Render"};
    // Get the dimensions of the output image.
    auto xSize = outputImage.GetXSize();
    auto ySize = outputImage.GetYSize();
    auto halfXSise = static_cast<double>(xSize) / 2.0;
    auto halfYSise = static_cast<double>(ySize) / 2.0;

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
    bool validInt{};
#pragma omp parallel for
    for(auto x : std::views::iota(0, xSize)) {
        normX = (static_cast<double>(x) * xFact) - 1.0;
        for(auto y : std::views::iota(0, ySize)) {
            // Normalize the x and y coordinates.
            normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the ray for this pixel.
            m_camera.GenerateRay(C_F(normX), C_F(normY), cameraRay);
            // Test for intersections with all objects in the scene.
            for(auto currentObject : m_objectList) {
                validInt = currentObject->TestIntersection(cameraRay, intPoint, localNormal, localColor);

                // If we have a valid intersection, change pixel color to red.
                if(validInt) {
                    // Compute intensity of illumination.
                    double intensity;
                    qbVector<double> color{3};
                    bool validIllum = false;
                    for(auto currentLight : m_lightList) {
                        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color,
                                                                       intensity);
                    }

                    // Compute the distance between the camera and the point of intersection.
                    double dist = (intPoint - cameraRay.m_point1).norm();
                    if(dist > maxDist)
                        maxDist = dist;

                    if(dist < minDist)
                        minDist = dist;

                    // outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
                    if(validIllum) {
                        outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
                    } else {
                        outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                    }
                } else {
                    outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                }
            }
        }
    }

    QBINFO("Minimum distance: {}", minDist);
    QBINFO("Maximum distance: {:.12f}", maxDist);

    return true;
}
