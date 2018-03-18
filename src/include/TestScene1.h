#pragma once
#include "Scene.h"
#include "PerspectiveCamera.h"
#include "Wavefront.h"

class TestScene1 : public Scene {
public:
    TestScene1();
    void update(float dt) override;
};