#pragma once

#include "BaseObject.h"
#include "Globals.h"

class Ball : public BaseObject
{
private:
    sf::CircleShape m_shape;
    float m_mass;
    bool m_static;
    sf::Vector2f m_velocity;
public:
    void __inline setStatic(bool t_static) { this->m_static = t_static; };
    float __inline getRadius() { return this->m_shape.getRadius(); }
    void __inline setMass(float t_mass) { this->m_mass = t_mass; }
    void randomizePosition();
    Ball();
    Ball(float t_mass);
    virtual void update(float f_delta) override;
    virtual void draw(sf::RenderTarget& renderTarget) override;
};