#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "RenderObject.h"
#include "Triangle.h"
#include "PerspectiveCamera.h"
#include "Scene.h"

class App {

public:
    App(unsigned int windowWidth, unsigned int windowHeight);
    ~App();
    unsigned int getWindowWidth();
    unsigned int getWindowHeight();

private:
    sf::RenderWindow* window;
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::vector<Scene*> scenes;
    size_t activeSceneId = 0;
    float fps;

    void init();
    void loadContent();
    void loop();
    void draw();
    void update(float dt);
};