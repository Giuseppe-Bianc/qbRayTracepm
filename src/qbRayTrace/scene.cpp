/* ***********************************************************
    scene.cpp

    The scene class implementation - A class to handle information
    about the scene and rendering to an image.

    This file forms part of the qbRayTrace project as described
    in the series of videos on the QuantitativeBytes YouTube
    channel.

    This code corresponds specifically to Episode 6 of the series,
    which may be found here:
    https://youtu.be/9K9ZYq6KgFY

    The whole series may be found on the QuantitativeBytes
    YouTube channel at:
    www.youtube.com/c/QuantitativeBytes

    GPLv3 LICENSE
    Copyright (c) 2021 Michael Bennett

***********************************************************/

// scene.cpp

#include "scene.hpp"
#include "./qbMaterials/simplematerial.hpp"

// The constructor.
qbRT::Scene::Scene() {
    // Configure the camera.
    // m_camera.SetPosition(	qbVector<double>{std::vector<double> {3.0, -3.75, -3.0}} );
    m_camera.SetPosition(qbVector<double>{std::vector<double>{3.0, -5.0, -2.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(0.75);
    m_camera.SetAspect(16.0 / 9.0);
    // m_camera.SetAspect(1.0);
    m_camera.UpdateCameraGeometry();

    // Create some materials.
    auto silverMetal = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto goldMetal = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto blueDiffuse = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto yellowDiffuse = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto orangeDiffuse = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto floorMaterial = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());
    auto wallMaterial = std::make_shared<qbRT::SimpleMaterial>(qbRT::SimpleMaterial());

    // Setup the materials.
    silverMetal->m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.8}};
    silverMetal->m_reflectivity = 0.5;
    silverMetal->m_shininess = 20.0;

    goldMetal->m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.8, 0.3}};
    goldMetal->m_reflectivity = 0.25;
    goldMetal->m_shininess = 20.0;

    blueDiffuse->m_baseColor = qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}};
    blueDiffuse->m_reflectivity = 0.05;
    blueDiffuse->m_shininess = 5.0;

    yellowDiffuse->m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}};
    yellowDiffuse->m_reflectivity = 0.05;
    yellowDiffuse->m_shininess = 5.0;

    orangeDiffuse->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
    orangeDiffuse->m_reflectivity = 0.05;
    orangeDiffuse->m_shininess = 5.0;

    floorMaterial->m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
    floorMaterial->m_reflectivity = 0.0;
    floorMaterial->m_shininess = 0.0;

    wallMaterial->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
    wallMaterial->m_reflectivity = 0.75;
    wallMaterial->m_shininess = 0.0;

    // Create and setup objects.
    auto cone = std::make_shared<qbRT::Cone>(qbRT::Cone());
    cone->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{0.0, 0.0, -0.5}},
                                          qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                          qbVector<double>{std::vector<double>{1.0, 1.0, 2.0}}});
    cone->AssignMaterial(silverMetal);

    auto leftSphere = std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere());
    leftSphere->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{1.5, -2.0, 0.5}},
                                                qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                                qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}});
    leftSphere->AssignMaterial(blueDiffuse);

    auto rightSphere = std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere());
    rightSphere->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
                                                 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                                 qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}});
    rightSphere->AssignMaterial(yellowDiffuse);

    auto topSphere = std::make_shared<qbRT::ObjSphere>(qbRT::ObjSphere());
    topSphere->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{0.0, 0.0, -1.0}},
                                               qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                               qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}});
    topSphere->AssignMaterial(orangeDiffuse);

    auto floor = std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane());
    floor->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
                                           qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                           qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    floor->AssignMaterial(floorMaterial);

    auto leftWall = std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane());
    leftWall->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
                                              qbVector<double>{std::vector<double>{0.0, -M_PI / 2.0, -M_PI / 2.0}},
                                              qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    leftWall->AssignMaterial(wallMaterial);

    auto backWall = std::make_shared<qbRT::ObjPlane>(qbRT::ObjPlane());
    backWall->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
                                              qbVector<double>{std::vector<double>{-M_PI / 2.0, 0.0, 0.0}},
                                              qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
    backWall->AssignMaterial(wallMaterial);

    auto cylinder1 = std::make_shared<qbRT::Cylinder>(qbRT::Cylinder());
    cylinder1->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{-1.5, -2.0, 1.0}},
                                               qbVector<double>{std::vector<double>{0.0, -M_PI / 2.0, 0.0}},
                                               qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
    cylinder1->AssignMaterial(goldMetal);

    auto cylinder2 = std::make_shared<qbRT::Cylinder>(qbRT::Cylinder());
    cylinder2->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
                                               qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                                               qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
    cylinder2->AssignMaterial(silverMetal);

    auto cone2 = std::make_shared<qbRT::Cone>(qbRT::Cone());
    cone2->SetTransformMatrix(qbRT::GTform{qbVector<double>{std::vector<double>{0.0, -1.0, 0.0}},
                                           qbVector<double>{std::vector<double>{M_PI / 4.0, 0.0, 0.0}},
                                           qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
    cone2->AssignMaterial(goldMetal);

    // Put the objects into the scene.
    m_objectList.emplace_back(cone);
    m_objectList.emplace_back(leftSphere);
    m_objectList.emplace_back(rightSphere);
    m_objectList.emplace_back(topSphere);
    m_objectList.emplace_back(floor);
    m_objectList.emplace_back(leftWall);
    m_objectList.emplace_back(backWall);
    m_objectList.emplace_back(cylinder1);
    m_objectList.emplace_back(cylinder2);
    m_objectList.emplace_back(cone2);

    // Construct and setup the lights.
    m_lightList.emplace_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    m_lightList.at(0)->m_location = qbVector<double>{std::vector<double>{3.0, -10.0, -5.0}};
    m_lightList.at(0)->m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};

    m_lightList.emplace_back(std::make_shared<qbRT::PointLight>(qbRT::PointLight()));
    m_lightList.at(1)->m_location = qbVector<double>{std::vector<double>{0.0, -10.0, -5.0}};
    m_lightList.at(1)->m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
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
        QBINFO("Processing line {}  of {}.", y, ySize);
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
