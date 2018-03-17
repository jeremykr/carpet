#include "Transformable.h"

Transformable::Transformable() {}

void Transformable::move(glm::vec3 direction) {
    pos += glm::rotate(quat, direction);
}

void Transformable::rotate(float angle, glm::vec3 axis, bool useRadians) {
    if (useRadians) angle = glm::radians(angle);
    axis = glm::rotate(quat, axis);
    quat = glm::angleAxis(angle, axis) * quat;
}