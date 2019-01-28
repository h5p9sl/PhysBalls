#pragma once

#include <SFML/Graphics.hpp>

// A class that manages and stores information about the current input
class Input
{
private: Input() = default;
public: ~Input() = default;
private:
    // These functions should be called whenever the user input is updated
    static void updateMouse(sf::Mouse::Button code, bool isDown);
    static void updateKey(sf::Keyboard::Key code, bool isDown);
public:
    // This function should be called every frame, before the input states are updated.
    // It copies every current input state over to the last input state.
    static void updateStates();
    // getLastState defines whether or not you want to get the state of the button last tick
    static bool getButtonDown(sf::Mouse::Button code, bool getLastState = false);
    static bool getKeyDown(sf::Keyboard::Key code, bool getLastState = false);

    // wasReleased is a parameter that tells the function whether or not you want to know if the user
    // has just released the button, or pressed it.
    static bool wasButtonPressed(sf::Mouse::Button code, bool wasReleased = false);
    static bool wasKeyPressed(sf::Keyboard::Key code, bool wasReleased = false);

public:
    static void handleInputEvent(const sf::Event& event);
};
