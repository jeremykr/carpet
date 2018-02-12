#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "RenderObject.h"
#include "Triangle.h"
#include "PerspectiveCamera.h"

class App {
public:
    App(unsigned int windowWidth, unsigned int windowHeight);
    void run();
    unsigned int getWindowWidth();
    unsigned int getWindowHeight();

private:
    sf::RenderWindow* window;
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::vector<RenderObject*> objects;
    Camera* camera;

    void init();
    void loadContent();
    void loop();
    void cleanup();
    void draw();
    void update();
};