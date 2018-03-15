#include "TestScene1.h"

TestScene1::TestScene1() {
    camera = new PerspectiveCamera(0.05, 1000, 800./600., 60);
    camera->pos = glm::vec3(0, 0, 2);
    objects.push_back(new TestTriangle());

    OBJ::OBJ obj = OBJ::parseFromFile("resources/cube.obj");
    OBJ::PointInfo p;

    for (OBJ::TriangleInfo t : obj.f) {
        std::cout << "Triangle" << std::endl;
        for (unsigned i = 0; i < 3; i++) {
            p = t.points[i];
            std::cout << "\tPoint " << i << std::endl;
            std::cout << "\t\tPosition" << std::endl;
            std::cout << "\t\t\t";
            for (auto x : obj.v[p.vIndex]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            std::cout << "\t\tTexture" << std::endl;
            std::cout << "\t\t\t";
            for (auto x : obj.vt[p.vtIndex]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            std::cout << "\t\tNormal" << std::endl;
            std::cout << "\t\t\t";
            for (auto x : obj.vn[p.vnIndex]) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

}

void TestScene1::update(float dt) {
    camera->move(glm::vec3(0, 0, 1) * dt);
    camera->rotate(1 * dt, glm::vec3(0, 0, 1));
}