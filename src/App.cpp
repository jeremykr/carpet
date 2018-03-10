#include "App.h"
#include "TestScene1.h"
#include <glm/gtx/string_cast.hpp>

App::App(unsigned int windowWidth, unsigned int windowHeight):
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    // The RenderWindow is required to set up an OpenGL context,
    // so we must include it here before initializing anything 
    // GL-related (including GLEW).
    window(
        new sf::RenderWindow(
            sf::VideoMode(windowWidth, windowHeight), 
            "Wow!"
        )
    )
{
    // Check if GLEW initializes successfully.
    // If so, run the app. If not, then we have to exit.
    if (glewInit() == GLEW_OK) {
        init();
        loadContent();
        loop();
    } else {
        std::cout << "GLEW failed to initialize." << std::endl;
    }
}

App::~App() {
    delete window;
    for (size_t i = 0; i < scenes.size(); i++) 
        delete scenes[i];
}

unsigned int App::getWindowWidth() { return windowWidth; }
unsigned int App::getWindowHeight() { return windowHeight; }

// Setup and load app content, including game objects and cameras.
void App::loadContent() {
    scenes.push_back(new TestScene1());
}

// Draw all active contents to the screen.
void App::draw() {
    scenes[activeSceneId]->draw();
    window->display();
}

// Update app contents.
// dt:  Time since last call.
void App::update(float dt) {
    scenes[activeSceneId]->update(dt);
}

// Main loop.
void App::loop() {

    float dt;
    float spf = 1/fps;
    auto timePrev = std::chrono::system_clock::now();
    auto timeNow = timePrev;
    auto timeElapsed = (std::chrono::duration<float>)0;

    while (window->isOpen()) {
        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        // Draw and update if the elapsed time since the last calls
        // is greater than the seconds-per-frame limit.
        timeNow = std::chrono::system_clock::now();
        timeElapsed += timeNow - timePrev;
        if ((dt = timeElapsed.count()) > spf) {
            App::draw();
            App::update(dt);
            timeElapsed = (std::chrono::duration<float>)0;
        }
        timePrev = timeNow;
    }
}

void App::init() {
    glClearColor(0, 0, 0, 0);
    fps = 60.0;
}
