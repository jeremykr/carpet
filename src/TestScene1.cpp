#include "TestScene1.h"

TestScene1::TestScene1() {
    camera = new PerspectiveCamera(0.05, 1000, 800./600., 60);
    camera->pos = glm::vec3(0, 0, 2);
    objects.push_back(new Triangle());
}

void TestScene1::update(float dt) {
    camera->pos += glm::vec3(0, 0, 1) * dt;
}