#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformable.h"

class Camera : public Transformable {
public:
    virtual glm::mat4 getProjectionMatrix() = 0;
    glm::mat4 getViewMatrix();

    float farPlane;
    float nearPlane;

protected:
    Camera(float nearPlane, float farPlane);
};