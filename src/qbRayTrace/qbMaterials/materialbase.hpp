#pragma once

#include "../qbLights/lightbase.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../qbPrimatives/objectbase.hpp"
#include "../ray.hpp"

namespace qbRT {
    class MaterialBase {
    public:
        MaterialBase() = default;
        virtual ~MaterialBase() = default;

        // Function to return the color of the material.
        virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                              const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                              const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                              const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                              const qbRT::Ray &cameraRay);

        // Function to compute diffuse color.
        static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                    const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                    const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                    const qbVector<double> &baseColor);

        // Function to compute the reflection color.
        qbVector<double> ComputeReflectionColor(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                const qbRT::Ray &incidentRay);

        // Function to cast a ray into the scene.
        bool CastRay(const qbRT::Ray &castRay, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                     const std::shared_ptr<qbRT::ObjectBase> &thisObject, std::shared_ptr<qbRT::ObjectBase> &closestObject,
                     qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                     qbVector<double> &closestLocalColor) const;

    public:
        // Counter for the number of relection rays.
        inline static int m_maxReflectionRays = 3;
        inline static int m_reflectionRayCount = 0;

    private:
    };
}  // namespace qbRT
