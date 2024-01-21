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

class MovementComponent {
private:
    sf::Sprite &sprite;

    float maxVelocity;
    sf::Vector2f direction;
    sf::Vector2f velocity;
    float acceleration;
    float deceleration;

    //Initializer FUnctions


public:
    virtual ~MovementComponent();

    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

    //Accessors
    float getMaxVelocity() const;

    const sf::Vector2f &getVelocity() const;

    //Function
    bool getState(MOVEMENT_STATES state) const;

    void setDirection(sf::Vector2f _direction);

    void update(const float &dt);

    void handleFriction(const float &dt);

    void checkVelocity();
};


#endif //SFML_MOVEMENTCOMPONENT_H
