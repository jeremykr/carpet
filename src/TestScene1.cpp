#include "TestScene1.h"

TestScene1::TestScene1() {
    camera = new PerspectiveCamera(0.05, 1000, 800./600., 60);
    camera->pos = glm::vec3(0, 0, 2);

    Wavefront::OBJ obj = Wavefront::parseOBJFile("resources/cube.obj");
    RenderObject cube = RenderObject::fromOBJ(obj);
    cube.material = Wavefront::parseMTLFile("resources/cube.mtl");

    cube.pos = glm::vec3(0, 0, -5);
    objects.push_back(cube);
}

void TestScene1::update(float dt) {
    for (RenderObject &o : objects) {
        if (!o.tag.compare("Cube")) {
            o.move(glm::vec3(1, 0, 0) * dt);
            o.rotate(dt, glm::vec3(1, 0, 0));
        }
    }
}