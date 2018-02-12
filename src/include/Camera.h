#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera {
public:
    Camera();
    virtual void move(glm::vec3 d);
    virtual void setPosition(glm::vec3 p);
    virtual void rotate(glm::quat q);
    virtual void setRotation(glm::quat q);
private:
    float aspectRatio;
    float farPlane;
    float nearPlane;
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::quat quat;
};