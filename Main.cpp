#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Globals.h"
#include "Ball.h"
#include "Input.h"

#include <math.h>

void processWindowMessages(sf::Window& window)
{
    sf::Event event;

    // Update input states
    Input::updateStates();

    while (window.pollEvent(event))
    {
        Input::handleInputEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}

void resetScene()
{
    for (auto pointer : globals->game.objects) {
        delete pointer;
    }
    globals->game.objects.clear();

    for (auto i = 0; i < 25; i++) {
        Ball* myBall = new Ball();
        globals->game.objects.push_back(new Ball());
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Simple Physics");
    globals = new Globals();
    globals->game.window = &window;

    srand(time(nullptr));

    resetScene();

    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen())
    {
        float f_delta = clock.getElapsedTime().asMicroseconds() / 1000.f / 1000.f;
        clock.restart();

        globals->globalTime++;
        processWindowMessages(window);

        if (Input::wasKeyPressed(sf::Keyboard::R, true)) {
            resetScene();
        }

        // Update all objects
        for (auto object : globals->game.objects) {
            object->update(f_delta);
        }

        window.clear();

        // Draw all objects
        for (auto object : globals->game.objects) {
            object->draw(window);
        }

        window.display();
    }

    return 0;
}
