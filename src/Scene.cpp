#include "Scene.h"

Scene::Scene() { }

Scene::~Scene() {
    delete camera;
}

void Scene::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (RenderObject o : objects) {
        o.draw(camera);
    }
}