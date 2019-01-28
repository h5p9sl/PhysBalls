#include "Ball.h"

#include <math.h>

Ball::Ball() :
    Ball((rand() % 50) / 100.f + 0.15f)
{
}

Ball::Ball(float t_mass)
    : m_mass(t_mass)
{
    m_shape.setRadius(this->m_mass * 10.f);

    float circleRadius = this->m_shape.getRadius();
    m_shape.setOrigin(circleRadius, circleRadius);
    this->randomizePosition();

    int oof = rand();
    this->m_shape.setFillColor({
        static_cast<uint8_t>(oof % 0xff),
        static_cast<uint8_t>(oof * 2 % 0xff),
        static_cast<uint8_t>(oof * 3 % 0xff)
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

void Ball::update(float f_delta) {
    m_shape.setRadius(this->m_mass * 10.f);
    float circleRadius = this->m_shape.getRadius();
    m_shape.setOrigin(circleRadius, circleRadius);

    if (!this->m_static) this->m_position += this->m_velocity;
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

            if (distance <= this->m_shape.getRadius() + object->m_shape.getRadius())
            {
                sf::Vector2f oVeloc[] = { this->m_velocity, object->m_velocity };

                if (object->m_static == true) {
                    // move *this out of the circumference of the other shape
                    this->m_position += vectorToObject;
                    this->m_velocity += vectorToObject;
                }

                // move *this out of the circumference of the other shape
                this->m_position += vectorToObject / this->m_mass;
                object->m_position += vectorToThis / object->m_mass;

                this->m_velocity = vectorToObject / this->m_mass;
                object->m_velocity = vectorToThis / object->m_mass;

                this->m_velocity.x += oVeloc[0].x;
                this->m_velocity.y += oVeloc[0].y;
                object->m_velocity.x += oVeloc[1].x;
                object->m_velocity.y += oVeloc[1].y;

            }
            else {
                this->m_velocity -= vectorToObject * object->m_mass / distance / this->m_mass;
            }

            sf::Vector2f windowSize = globals->game.window->getView().getSize();
            const float radius = this->m_shape.getRadius();

            // if (this->m_position.x + radius > windowSize.x) {
            //     this->m_position.x = windowSize.x - radius;
            //     this->m_velocity.x = -this->m_velocity.x * 0.25f;
            // }
            // if (this->m_position.y + radius > windowSize.y) {
            //     this->m_position.y = windowSize.y - radius;
            //     this->m_velocity.y = -this->m_velocity.y * 0.25f;
            // }
            // if (this->m_position.x - radius < 0.f) {
            //     this->m_position.x = 0.f + radius;
            //     this->m_velocity.x = -this->m_velocity.x * 0.25f;
            // }
            // if (this->m_position.y - radius < 0.f) {
            //     this->m_position.y = 0.f + radius;
            //     this->m_velocity.y = -this->m_velocity.y * 0.25f;
            // }

        }
    }
}

void Ball::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(this->m_shape);
}
