#pragma once
#include "Scene.h"
#include "TestTriangle.h"
#include "PerspectiveCamera.h"
#include "OBJ.h"

class TestScene1 : public Scene {
public:
    TestScene1();
    void update(float dt) override;
};