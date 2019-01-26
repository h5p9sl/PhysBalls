#pragma once

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
    sf::Vector2f m_position;
public:
    virtual void update(float f_delta) = 0;
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
};