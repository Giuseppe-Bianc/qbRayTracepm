#pragma once

#include "../headers.h"
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"

namespace qbRT {
    class Camera {
    public:
        // The default constructor.
        Camera();

        void SetPosition(const qbVector<double> &newPosition) { m_cameraPosition = newPosition; }
        void SetLookAt(const qbVector<double> &newLookAt) { m_cameraLookAt = newLookAt; }
        void SetUp(const qbVector<double> &upVector) { m_cameraUp = upVector; }
        void SetLength(double newLength) { m_cameraLength = newLength; }
        void SetHorzSize(double newHorzSize) { m_cameraHorzSize = newHorzSize; }
        void SetAspect(double newAspect) { m_cameraAspectRatio = newAspect; }

        // Method to return the position of the camera.
        inline qbVector<double> GetPosition() const { return m_cameraPosition; }
        // Method to return the LookAt of the camera.
        inline qbVector<double> GetLookAt() const { return m_cameraLookAt; }
        // Method to return the up vector of the camera.
        inline qbVector<double> GetUp() const { return m_cameraUp; }
        // Method to return the length of the camera.
        inline double GetLength() const { return m_cameraLength; }
        // Method to return the horizontal size.
        inline double GetHorzSize() const { return m_cameraHorzSize; }
        // Method to return the camera aspect ratio.
        inline double GetAspect() const { return m_cameraAspectRatio; }
        // Method to return the U vector.
        inline qbVector<double> GetU() const { return m_projectionScreenU; }
        // Method to return the V vector.
        inline qbVector<double> GetV() const { return m_projectionScreenV; }
        // Method to return the projection screen centre.
        inline qbVector<double> GetScreenCentre() const { return m_projectionScreenCentre; }

        // Function to generate a ray.
        bool GenerateRay(double proScreenX, double proScreenY, qbRT::Ray &cameraRay) const;

        // Function to update the camera geometry.
        void UpdateCameraGeometry();

    private:
        qbVector<double> m_cameraPosition{3};
        qbVector<double> m_cameraLookAt{3};
        qbVector<double> m_cameraUp{3};
        double m_cameraLength;
        double m_cameraHorzSize;
        double m_cameraAspectRatio;

        qbVector<double> m_alignmentVector{3};
        qbVector<double> m_projectionScreenU{3};
        qbVector<double> m_projectionScreenV{3};
        qbVector<double> m_projectionScreenCentre{3};
    };
}  // namespace qbRT
