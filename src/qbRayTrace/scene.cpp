#include "scene.hpp"
#include "./qbMaterials/simplematerial.hpp"
#include "./qbMaterials/simplerefractive.hpp"
#include "./qbTextures/checker.hpp"
#include "./qbTextures/image.hpp"

// The constructor.
qbRT::Scene::Scene() {
    // **************************************************************************************
    // Configure the camera.
    // **************************************************************************************
    m_camera.SetPosition({{3.0, -5.0, 0.25}});
    m_camera.SetLookAt({{0.0, 0.0, 0.0}});
    m_camera.SetUp({{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(1.0);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // **************************************************************************************
    // Setup ambient lightling.
    // **************************************************************************************
    qbRT::MaterialBase::m_ambientColor = {{1.0, 1.0, 1.0}};
    qbRT::MaterialBase::m_ambientIntensity = 0.2;

    // **************************************************************************************
    // Create some textures.
    // **************************************************************************************
    auto floorTexture = std::make_shared<qbRT::Texture::Checker>();
    auto imageTexture = std::make_shared<qbRT::Texture::Image>();

    // **************************************************************************************
    // Setup the textures.
    // **************************************************************************************
    floorTexture->SetTransform({{0.0, 0.0}}, 0.0, {{16.0, 16.0}});

    imageTexture->LoadImage("C:/dev/visualStudio/qbRayTracepm/src/testImage.bmp");
    imageTexture->SetTransform({{0.0, 0.0}}, 0.0, {{1.0, 1.0}});

    // **************************************************************************************
    // Create some materials.
    // **************************************************************************************
    auto floorMaterial = std::make_shared<qbRT::SimpleMaterial>();
    auto imageMaterial = std::make_shared<qbRT::SimpleMaterial>();
    auto sphereMaterial = std::make_shared<qbRT::SimpleMaterial>();
    auto sphereMaterial2 = std::make_shared<qbRT::SimpleMaterial>();
    auto sphereMaterial3 = std::make_shared<qbRT::SimpleMaterial>();
    auto coneMaterial = std::make_shared<qbRT::SimpleMaterial>();
    auto glassMaterial = std::make_shared<qbRT::SimpleRefractive>();

    // **************************************************************************************
    // Setup the materials.
    // **************************************************************************************
    floorMaterial->m_baseColor = {{1.0, 1.0, 1.0}};
    floorMaterial->m_reflectivity = 0.25;
    floorMaterial->m_shininess = 0.0;
    floorMaterial->AssignTexture(floorTexture);

    imageMaterial->m_baseColor = {{1.0, 0.125, 0.125}};
    imageMaterial->m_reflectivity = 0.0;
    imageMaterial->m_shininess = 0.0;
    imageMaterial->AssignTexture(imageTexture);

    sphereMaterial->m_baseColor = {{1.0, 0.2, 0.2}};
    sphereMaterial->m_reflectivity = 0.8;
    sphereMaterial->m_shininess = 32.0;

    sphereMaterial2->m_baseColor = {{0.2, 1.0, 0.2}};
    sphereMaterial2->m_reflectivity = 0.8;
    sphereMaterial2->m_shininess = 32.0;

    sphereMaterial3->m_baseColor = {{0.2, 0.2, 1.0}};
    sphereMaterial3->m_reflectivity = 0.8;
    sphereMaterial3->m_shininess = 32.0;

    coneMaterial->m_baseColor = {{0.8, 0.8, 0.2}};
    coneMaterial->m_reflectivity = 0.15;
    coneMaterial->m_shininess = 32.0;

    glassMaterial->m_baseColor = {{0.7, 0.7, 0.2}};
    glassMaterial->m_reflectivity = 0.25;
    glassMaterial->m_shininess = 32.0;
    glassMaterial->m_translucency = 0.5;
    glassMaterial->m_ior = 1.57;

    // **************************************************************************************
    // Create and setup objects.
    // **************************************************************************************
    auto floor = std::make_shared<qbRT::ObjPlane>();
    floor->SetTransformMatrix(qbRT::GTform{{{0.0, 0.0, 1.0}}, {{0.0, 0.0, 0.0}}, {{16.0, 16.0, 1.0}}});
    floor->AssignMaterial(floorMaterial);

    // **************************************************************************************
    auto imagePlane = std::make_shared<qbRT::ObjPlane>();
    imagePlane->SetTransformMatrix(qbRT::GTform{{{2.0, 5.0, -0.75}}, {{-pi / 2.0, 0.0, 0.0}}, {{1.75, 1.75, 1.0}}});
    imagePlane->AssignMaterial(imageMaterial);

    // **************************************************************************************
    auto sphere = std::make_shared<qbRT::ObjSphere>();
    sphere->SetTransformMatrix(qbRT::GTform{{{-2.0, -2.0, 0.25}}, {{0.0, 0.0, 0.0}}, {{0.75, 0.75, 0.75}}});
    sphere->AssignMaterial(sphereMaterial);

    // **************************************************************************************
    auto sphere2 = std::make_shared<qbRT::ObjSphere>();
    sphere2->SetTransformMatrix(qbRT::GTform{{{-2.0, -0.5, 0.25}}, {{0.0, 0.0, 0.0}}, {{0.75, 0.75, 0.75}}});
    sphere2->AssignMaterial(sphereMaterial2);

    // **************************************************************************************
    auto sphere3 = std::make_shared<qbRT::ObjSphere>();
    sphere3->SetTransformMatrix(qbRT::GTform{{{-2.0, -1.25, -1.0}}, {{0.0, 0.0, 0.0}}, {{0.75, 0.75, 0.75}}});
    sphere3->AssignMaterial(sphereMaterial3);

    // **************************************************************************************
    auto rmSphere = std::make_shared<qbRT::RM::Sphere>();
    rmSphere->SetTransformMatrix(qbRT::GTform{{{0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}}, {{1.0, 1.0, 1.0}}});
    rmSphere->AssignMaterial(coneMaterial);

    auto rmTorus = std::make_shared<qbRT::RM::Torus>();
    rmTorus->SetRadii(0.7, 0.3);
    rmTorus->SetTransformMatrix(qbRT::GTform{{{2.0, 0.0, 0.0}}, {{-pi / 2.0, 0.0, 0.0}}, {{1.0, 1.0, 1.0}}});
    rmTorus->AssignMaterial(glassMaterial);

    auto rmCube = std::make_shared<qbRT::RM::Cube>();
    rmCube->SetTransformMatrix(qbRT::GTform{{{3.5, 0.0, 0.0}}, {{0.0, 0.0, -pi / 4.0}}, {{0.5, 0.5, 0.5}}});
    rmCube->AssignMaterial(coneMaterial);

    // **************************************************************************************
    // Put the objects into the scene.
    // **************************************************************************************
    m_objectList.emplace_back(floor);
    m_objectList.emplace_back(imagePlane);
    m_objectList.emplace_back(sphere);
    m_objectList.emplace_back(sphere2);
    m_objectList.emplace_back(sphere3);
    m_objectList.emplace_back(rmSphere);
    m_objectList.emplace_back(rmTorus);
    m_objectList.emplace_back(rmCube);

    // **************************************************************************************
    // Construct and setup the lights.
    // **************************************************************************************
    m_lightList.emplace_back(std::make_shared<qbRT::PointLight>());
    m_lightList.at(0)->m_location = {{3.0, -10.0, -5.0}};
    m_lightList.at(0)->m_color = {{1.0, 1.0, 1.0}};
    m_lightList.at(0)->m_intensity = 4.0;

    m_lightList.emplace_back(std::make_shared<qbRT::PointLight>());
    m_lightList.at(1)->m_location = {{0.0, -10.0, -5.0}};
    m_lightList.at(1)->m_color = {{1.0, 1.0, 1.0}};
    m_lightList.at(1)->m_intensity = 2.0;
}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage) const {
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
    Timer Timerr{"Render"};
    for(int y = 0; y < ySize; ++y) {
        normY = (static_cast<double>(y) * yFact) - 1.0;
        QBINFO("Processing line {} of {}.", y, ySize);
        for(int x = 0; x < xSize; ++x) {
            // Normalize the x and y coordinates.
            normX = (static_cast<double>(x) * xFact) - 1.0;

            // Generate the ray for this pixel.
            m_camera.GenerateRay(normX, normY, cameraRay);

            // Test for intersections with all objects in the scene.
            std::shared_ptr<qbRT::ObjectBase> closestObject;
            qbVector<double> closestIntPoint{3};
            qbVector<double> closestLocalNormal{3};
            qbVector<double> closestLocalColor{3};
            bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

            /* Compute the illumination for the closest object, assuming that there
                was a valid intersection. */
            if(intersectionFound) {
                // Check if the object has a material.
                if(closestObject->m_hasMaterial) {
                    // Use the material to compute the color.
                    qbRT::MaterialBase::m_reflectionRayCount = 0;
                    qbVector<double> color = closestObject->m_pMaterial->ComputeColor(
                        m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);
                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                } else {
                    // Use the basic method to compute the color.
                    qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList, closestObject,
                                                                                        closestIntPoint, closestLocalNormal,
                                                                                        closestObject->m_baseColor);
                    outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                }
            }
        }
    }

    std::cout << std::endl;
    return true;
}

// Function to cast a ray into the scene.
bool qbRT::Scene::CastRay(const qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                          qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                          qbVector<double> &closestLocalColor) const {
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};
    double minDist = 1e6;
    bool intersectionFound = false;
    for(const auto &currentObject : m_objectList) {
        bool validInt = currentObject->TestIntersection(castRay, intPoint, localNormal, localColor);

        // If we have a valid intersection.
        if(validInt) {
            // Set the flag to indicate that we found an intersection.
            intersectionFound = true;

            // Compute the distance between the camera and the point of intersection.
            double dist = (intPoint - castRay.m_point1).norm();

            /* If this object is closer to the camera than any one that we have
                seen before, then store a reference to it. */
            if(dist < minDist) {
                minDist = dist;
                closestObject = currentObject;
                closestIntPoint = intPoint;
                closestLocalNormal = localNormal;
                closestLocalColor = localColor;
            }
        }
    }

    return intersectionFound;
}
