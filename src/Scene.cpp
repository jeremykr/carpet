#include "Scene.h"

Scene::Scene() { }

void Scene::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (RenderObject* o : objects) {
        o->draw(camera);
    }
}