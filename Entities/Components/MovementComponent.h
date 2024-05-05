#ifndef SFML_MOVEMENTCOMPONENT_H
#define SFML_MOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include "../../enums/movement_states.cpp"
#include "MovementData.h"

class MovementComponent {
private:
    sf::Sprite &sprite;


    __attribute__((unused)) void debugVelocity() const;
    //Initializer FUnctions


public:
    MovementData md;

    virtual ~MovementComponent();

    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

    //Accessors
    float getMaxVelocity() const;

    float getVelocityMagnitude() const;

    const sf::Vector2f &getVelocity() const;

    //Function
    bool getState(MOVEMENT_STATES state) const;

    void setDirection(sf::Vector2f _direction);

    void update(const MovementData &next);

    static void handleFriction(MovementData &_md, const float &dt);

    static void checkVelocity(MovementData &_md);

    MovementData nextMovementData(const float &dt) const;

    MovementData nextMovementData(const float &dt, std::tuple<bool, bool> forbidden_directions) const;

    static MovementData processNextMovementData(const float &dt, MovementData next);
};


#endif //SFML_MOVEMENTCOMPONENT_H
