#pragma once
#include "Scene.h"
#include "Triangle.h"
#include "PerspectiveCamera.h"

class TestScene1 : public Scene {
public:
    TestScene1();
    void update(float dt) override;
};