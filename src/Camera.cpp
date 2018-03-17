#include "Camera.h"

Camera::Camera(float nearPlane, float farPlane) :
    Transformable(),
    nearPlane(nearPlane),
    farPlane(farPlane)
{ }

glm::mat4 Camera::getViewMatrix() {
    return 
        glm::toMat4(glm::inverse(quat)) * 
        glm::inverse(glm::translate(glm::mat4(), pos));
}