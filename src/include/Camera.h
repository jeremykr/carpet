#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    virtual void move(glm::vec3 d);
    virtual void rotate(glm::quat q);
    virtual glm::mat4 getProjectionMatrix() = 0;
    glm::mat4 getViewMatrix();

    float farPlane;
    float nearPlane;
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::quat quat;

protected:
    Camera(float nearPlane, float farPlane);
};