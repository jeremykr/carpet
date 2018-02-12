#include "App.h"
#include <glm/gtx/string_cast.hpp>

App::App(unsigned int windowWidth, unsigned int windowHeight):
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    window(
        new sf::RenderWindow(
            sf::VideoMode(windowWidth, windowHeight), 
            "Wow!"
        )
    ),
    camera(
        new PerspectiveCamera(0.05, 1000, 800./600., 60)
    )
    { }

unsigned int App::getWindowWidth() { return windowWidth; }
unsigned int App::getWindowHeight() { return windowHeight; }

void App::init() {
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize." << std::endl;
    } else {
        std::cout << "GLEW successfully initialized." << std::endl;
    }
    glClearColor(0, 0, 0, 0);
}

void App::loadContent() {
    camera->pos = glm::vec3(0, 0, 2);
    objects.push_back(new Triangle());
}

void App::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (RenderObject* o : objects) {
        o->draw(camera);
    }
    window->display();
}

void App::update() {
    
}

void App::loop() {
    while (window->isOpen()) {
        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        App::draw();
        App::update();
    }
}

void App::cleanup() { }

void App::run() {
    init();
    loadContent();
    loop();
    cleanup();
}