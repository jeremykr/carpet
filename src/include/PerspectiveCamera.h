#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(
        float nearPlane,
        float farPlane,
        float aspectRatio, 
        float fieldOfView
    );

    glm::mat4 getProjectionMatrix() override;
    
private:
    float aspectRatio;
    float fieldOfView;
    glm::mat4 projectionMatrix;
};