#ifndef SFML_MOVEMENTDATA_H
#define SFML_MOVEMENTDATA_H

#include <System/Vector2.hpp>
#include <valarray>

struct MovementData {

    MovementData(float maxVelocity, float acceleration, float deceleration) : maxVelocity(maxVelocity),
                                                                              acceleration(acceleration),
                                                                              deceleration(deceleration) {
        this->direction = sf::Vector2f(0.f, 0.f);
        this->position = sf::Vector2f(0.f, 0.f);
        this->velocity = sf::Vector2f(0.f, 0.f);
    }

    MovementData(const MovementData &movementData) {
        maxVelocity = movementData.maxVelocity;
        acceleration = movementData.acceleration;
        deceleration = movementData.deceleration;
        direction = movementData.direction;
        position = movementData.position;
        velocity = movementData.velocity;
    }

    virtual ~MovementData() = default;

    float maxVelocity;
    float acceleration;
    float deceleration;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

#endif //SFML_MOVEMENTDATA_H


