#include "Ball.h"

#include <math.h>

Ball::Ball() :
    Ball((rand() % 50) / 100.f + 0.15f)
{
}

Ball::Ball(float t_mass)
    :
    m_mass(t_mass),
    m_static(false)
{
    m_shape.setRadius(this->m_mass * 10.f);

    float circleRadius = this->m_shape.getRadius();
    m_shape.setOrigin(circleRadius, circleRadius);
    this->randomizePosition();

    int r = rand();
    int g = rand();
    int b = rand();
    this->m_shape.setFillColor({
        static_cast<uint8_t>(r % 0xff),
        static_cast<uint8_t>(g % 0xff),
        static_cast<uint8_t>(b % 0xff)
        });

}

void Ball::randomizePosition()
{
    float circleRadius = this->m_shape.getRadius();
    sf::Vector2f windowSize = globals->game.window->getView().getSize();
    sf::Vector2f randomPosition = {
        static_cast<float>(rand() % ((int)windowSize.x - (int)circleRadius) + circleRadius),
        static_cast<float>(rand() % ((int)windowSize.y - (int)circleRadius) + circleRadius)
    };
    this->m_position = randomPosition;
    this->m_shape.setPosition(this->m_position);
}

// Called once every frame before being drawn.
void Ball::update(float f_delta) {
    
    // FIXME: This shouldn't really be here
    if (this->m_static) {
        this->m_shape.setRadius(this->m_mass * 10.f);
        float circleRadius = this->m_shape.getRadius();
        m_shape.setOrigin(circleRadius, circleRadius);
    }
    else {
        // Apply velocity to position
        this->m_position += this->m_velocity;
    }
    // Update position
    this->m_shape.setPosition(this->m_position);

    for (auto object : globals->game.objects) {

        if (object != this) {

            sf::Vector2f vectorToObject = { this->m_position - object->m_position };
            sf::Vector2f vectorToThis = { object->m_position - this->m_position };
            float distance = sqrtf( powf(vectorToObject.x, 2) + powf(vectorToObject.y, 2) );

            // Normalize vectors
            vectorToObject /= distance;
            vectorToThis /= distance;

            float distance_frm_surfaces = distance - this->getRadius() - object->getRadius();
            
            // Collision detection
            if (distance_frm_surfaces <= 0.f)
            {
                // NOTE: From this point on, stuff stops making sense.

                sf::Vector2f oVeloc[] = { this->m_velocity, object->m_velocity };

                // If the other object doesn't obey the laws of physics :P
                if (object->m_static == true) {
                    // move *this out of the circumference of the other shape
                    this->m_position += vectorToObject;
                    this->m_velocity += vectorToObject;
                }

                // move *this out of the circumference of the other shape
                this->m_position += vectorToObject / this->m_mass;
                object->m_position += vectorToThis / object->m_mass;

                // Apply the same amount of velocity used when colliding with the object
                this->m_velocity = vectorToObject / this->m_mass;
                object->m_velocity = vectorToThis / object->m_mass;

                // Add original velocity for some reason, idk
                this->m_velocity.x += oVeloc[0].x;
                this->m_velocity.y += oVeloc[0].y;
                object->m_velocity.x += oVeloc[1].x;
                object->m_velocity.y += oVeloc[1].y;
            }
            else {
                // No collision detected;
                // Attract this object to other objects using some fancy math that I made up
                this->m_velocity -= vectorToObject * object->m_mass / distance / this->m_mass;
            }
        }
    }
}

void Ball::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(this->m_shape);
}
