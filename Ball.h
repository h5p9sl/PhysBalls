#pragma once

#include "BaseObject.h"
#include "Globals.h"

class Ball : public BaseObject
{
private:
    sf::CircleShape m_shape;
    float m_mass;
    sf::Vector2f m_velocity;
public:
    float __inline getRadius() { return this->m_shape.getRadius(); }
    void randomizePosition();
    Ball();
    Ball(float t_mass);
    virtual void update(float f_delta) override;
    virtual void draw(sf::RenderTarget& renderTarget) override;
};