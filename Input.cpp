#include "Input.h"

#include <cstring> // memcpy, memset
#include <iostream>

// A 2 by (?) matrix, the 2 rows being the current state and the last state, which is updated every tick
bool mouse[2][6] = { false };
bool keyboard[2][256] = { false };

void Input::updateMouse(sf::Mouse::Button code, bool isDown) {
    mouse[0][code] = isDown;
}

void Input::updateKey(sf::Keyboard::Key code, bool isDown) {
    keyboard[0][code] = isDown;
}

void Input::updateStates() {
    // Copy current states over to last states
    std::memcpy((void*)keyboard[1], (void*)keyboard[0], sizeof(keyboard[0]));
    std::memcpy((void*)mouse[1], (void*)mouse[0], sizeof(mouse[0]));
}

void Input::handleInputEvent(const sf::Event& event) {
    bool isPressed = false;
    bool isKeyboardEvent = (event.type == sf::Event::KeyPressed) ||
        (event.type == sf::Event::KeyReleased);

    switch (event.type)
    {
    case sf::Event::KeyPressed:
    case sf::Event::MouseButtonPressed:
        isPressed = true;
    case sf::Event::KeyReleased:
    case sf::Event::MouseButtonReleased:
        (isKeyboardEvent) ? updateKey(event.key.code, isPressed) :
            updateMouse(event.mouseButton.button, isPressed);
        break;
    }
}

bool Input::getButtonDown(sf::Mouse::Button code, bool getLastState) {
    return (getLastState) ? mouse[1][code] : mouse[0][code];
}

bool Input::getKeyDown(sf::Keyboard::Key code, bool getLastState) {
    return (getLastState) ? keyboard[1][code] : keyboard[0][code];
}


bool Input::wasButtonPressed(sf::Mouse::Button code, bool wasReleased) {
    return Input::getButtonDown(code, wasReleased) &&
        !Input::getButtonDown(code, !wasReleased);
}

bool Input::wasKeyPressed(sf::Keyboard::Key code, bool wasReleased) {
    return Input::getKeyDown(code, wasReleased) &&
        !Input::getKeyDown(code, !wasReleased);
}
