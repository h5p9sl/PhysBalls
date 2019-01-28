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
        // TODO: Cleanup this ugly code
        case sf::Event::MouseWheelScrolled:
            static float zoom = 1.f;
            float delta = event.mouseWheelScroll.delta; 
            auto view = globals->game.window->getView();
            if (zoom > 1.f && delta > 0.f || zoom < 1.f && delta < 0.f) { zoom = 1.f; }
            zoom -= event.mouseWheelScroll.delta * 0.05f;
            std::cout << "zoomFactor = " << zoom << std::endl;
            view.zoom(zoom);
            globals->game.window->setView(view);
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
#ifndef _DEBUG
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Simple Physics");
#else
    sf::RenderWindow window(sf::VideoMode(640, 480), "Simple Physics");
#endif
    globals = new Globals();
    globals->game.window = &window;

    srand(time(nullptr));

    resetScene();

    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen())
    {
        float f_delta = clock.getElapsedTime().asSeconds();
        clock.restart();

        globals->globalTime++;
        processWindowMessages(window);
        
        // TODO: Cleanup this ugly code #2
        {
        static Ball* myBall = nullptr;
        static float mass = 2.f;
        static std::vector<Ball*>::const_iterator myBallIter[2];
        if (Input::getButtonDown(sf::Mouse::Left) &&
            !Input::getKeyDown(sf::Keyboard::R))
        {
            if (!Input::getButtonDown(sf::Mouse::Left, true)) {
                myBall = new Ball(mass);
                myBall->setStatic(true);
                myBallIter[0] = globals->game.objects.cend();
                globals->game.objects.push_back(myBall);
                myBallIter[1] = globals->game.objects.cend();
            }

            if (Input::getKeyDown(sf::Keyboard::Up)) {
                mass += 5.f * f_delta;
                myBall->setMass(mass);
            }
            else if (Input::getKeyDown(sf::Keyboard::Down)) {
                mass -= 5.f * f_delta;
                myBall->setMass(mass);
            }

            auto pos = sf::Mouse::getPosition(*globals->game.window);
            auto fpos = globals->game.window->mapPixelToCoords(pos);
            myBall->setPosition(fpos);
        }
        else if (Input::wasButtonPressed(sf::Mouse::Left, true) && myBall != nullptr) {
            globals->game.objects.erase(myBallIter[0], myBallIter[1]);
            delete myBall;
        }
        }

        // TODO: Clean up this ugly code #3
        if (Input::getButtonDown(sf::Mouse::Middle)) {
            static sf::Vector2f mouseStart;
            static sf::Vector2f centerStart;
            sf::Vector2f mouseDelta;
            sf::Vector2f newCenter;

            auto view = globals->game.window->getView();
            auto center = view.getCenter();
            auto pos = sf::Mouse::getPosition(*globals->game.window);
            auto fpos = globals->game.window->mapPixelToCoords(pos);
            
            if (!Input::getButtonDown(sf::Mouse::Middle, true)) {
                mouseStart = fpos;
                centerStart = center;
            }
            mouseDelta = mouseStart - fpos;
            newCenter = centerStart + mouseDelta;
            
            view.setCenter(center + mouseDelta);
            globals->game.window->setView(view);
        }

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
