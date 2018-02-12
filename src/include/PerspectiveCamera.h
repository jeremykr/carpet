#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera();
private:
    float fov;
    glm::mat4 projectionMatrix;
};