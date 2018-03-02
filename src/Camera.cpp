#include "Camera.h"

Camera::Camera(float nearPlane, float farPlane):
    nearPlane(nearPlane),
    farPlane(farPlane)
{ }

glm::mat4 Camera::getViewMatrix() {
    return 
        glm::toMat4(glm::inverse(quat)) * 
        glm::inverse(glm::translate(glm::mat4(), pos));
}

void Camera::move(glm::vec3 direction) {
    pos += glm::rotate(quat, direction);
}

void Camera::rotate(float angle, glm::vec3 axis, bool useRadians) {
    if (useRadians) angle = glm::radians(angle);
    axis = glm::rotate(quat, axis);
    quat = glm::angleAxis(angle, axis) * quat;
}