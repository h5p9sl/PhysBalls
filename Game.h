#pragma once

#include <SFML/Graphics.hpp>

class Ball;

class Game
{
public:
    sf::RenderWindow* window;
    std::vector<Ball*> objects;
public:
    Game();
};