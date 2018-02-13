#pragma once
#include "RenderObject.h"
#include "Camera.h"
#include <vector>

class Scene {
public:
    std::vector<RenderObject*> objects;
    Camera* camera;

    void draw();
    virtual void update(float dt) = 0;

protected:
    Scene();
};