#include "camera.hpp"

qbRT::Camera::Camera() {
    // The default constructor.
    m_cameraPosition = qbVector<double>{{0.0, -10.0, 0.0}};
    m_cameraLookAt = qbVector<double>{{0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{{0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;
}

// Function to compute camera geometry.
void qbRT::Camera::UpdateCameraGeometry() {
    // First, compute the vector from the camera position to the LookAt position.
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // Second, compute the U and V vectors.
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    // Thirdly, compute the positon of the centre point of the screen.
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    // Modify the U and V vectors to match the size and aspect ratio.
    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool qbRT::Camera::GenerateRay(double proScreenX, double proScreenY, qbRT::Ray &cameraRay) const {
    // Compute the location of the screen point in world coordinates.
    qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

    // Use this point along with the camera position to compute the ray.
    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point2 = screenWorldCoordinate;
    cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;

    return true;
}
