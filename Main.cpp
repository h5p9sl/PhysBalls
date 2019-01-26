#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Globals.h"
#include "Ball.h"

#include <math.h>

void processWindowMessages(sf::Window& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
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

        static bool downlastState = false;
        static bool downcurrState = false;
        downcurrState = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        if (downcurrState && !downlastState) {
            resetScene();
        }
        downlastState = downcurrState;

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
