#include "App.h"

App::App(unsigned int windowWidth, unsigned int windowHeight):
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    window(
        new sf::RenderWindow(
            sf::VideoMode(windowWidth, windowHeight), 
            "Wow!"
        )
    ) { }

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
    objects.push_back(new Triangle());
}

void App::draw() {
    for (RenderObject* o : objects) {
        o->draw();
    }
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
        window->display();
    }
}

void App::cleanup() { }

void App::run() {
    init();
    loadContent();
    loop();
    cleanup();
}