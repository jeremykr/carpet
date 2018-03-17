#include "Scene.h"

Scene::Scene() { }

Scene::~Scene() {
    //for (size_t i = 0; i < objects.size(); i++)
      //  delete objects[i];
    delete camera;
}

void Scene::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (RenderObject o : objects) {
        o.draw(camera);
    }
}