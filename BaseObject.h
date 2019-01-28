#pragma once

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
    sf::Vector2f m_position;
public:
    virtual void update(float f_delta) = 0;
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
public:
    sf::Vector2f __inline getPosition() { return this->m_position; }
    void __inline setPosition(const sf::Vector2f& t_position) { this->m_position = t_position; }
};