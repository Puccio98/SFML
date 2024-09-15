#ifndef SFML_MOVEMENTDATA_H
#define SFML_MOVEMENTDATA_H

#include <System/Vector2.hpp>
#include <valarray>
#include <optional>
#include "../../enums/directions.cpp"

struct MovementData {

    MovementData(float maxVelocity, float acceleration, float deceleration, sf::Vector2f position) :
            maxVelocity(maxVelocity),
            acceleration(acceleration),
            deceleration(deceleration),
            position(position) {
        this->accelerationDirection = sf::Vector2f(0.f, 0.f);
        this->facingDirection = std::make_pair(std::nullopt, DIRECTIONS::DOWN);

        this->velocity = sf::Vector2f(0.f, 0.f);
    }

    MovementData(const MovementData &movementData) {
        maxVelocity = movementData.maxVelocity;
        acceleration = movementData.acceleration;
        deceleration = movementData.deceleration;
        accelerationDirection = movementData.accelerationDirection;
        facingDirection = movementData.facingDirection;
        position = movementData.position;
        velocity = movementData.velocity;
    }

    virtual ~MovementData() = default;

    float maxVelocity;
    float acceleration;
    float deceleration;
    /**
     * Direzione dell'accelerazione
     */
    sf::Vector2f accelerationDirection;
    /**
     * Contiene le direzioni verso cui è rivolto il personaggio, viene sempre specificato se il personaggio è rivolto verso il basso o verso l'alto.
     * La direzione orizzontale è opzionale.
     */
    std::pair<std::optional<DIRECTIONS>, DIRECTIONS> facingDirection;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

#endif //SFML_MOVEMENTDATA_H


