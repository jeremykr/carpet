#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(
    float nearPlane,
    float farPlane,
    float aspectRatio, 
    float fieldOfView
    ):
    Camera(nearPlane, farPlane),
    aspectRatio(aspectRatio),
    fieldOfView(fieldOfView),
    projectionMatrix(
        glm::perspective(
            glm::radians(fieldOfView),
            aspectRatio,
            nearPlane,
            farPlane
        )
    )
{ }

glm::mat4 PerspectiveCamera::getProjectionMatrix() { 
    return projectionMatrix;
}