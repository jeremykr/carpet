#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Camera::Camera(float nearPlane, float farPlane):
    nearPlane(nearPlane),
    farPlane(farPlane)
{ }

glm::mat4 Camera::getViewMatrix() {
    return 
        glm::toMat4(glm::inverse(quat)) * 
        glm::inverse(glm::translate(glm::mat4(), pos));
}

void Camera::move(glm::vec3 d) {

}

void Camera::rotate(glm::quat q) {

}