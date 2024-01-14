#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite),
          maxVelocity(maxVelocity),
          acceleration(acceleration),
          deceleration(deceleration) {
}

MovementComponent::~MovementComponent() {

}

//Functions
void MovementComponent::update(const float &dt) {
    //Decelerate sprite and control max velocity. Then moves sprite.
    if (this->velocity.x > 0.f) {
        //m velocity check
        if (this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;

        //Deceleration x positive
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0;
    } else if (this->velocity.x < 0.f) {
        if (this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;

        //Deceleration x negative
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0;
    }

    if (this->velocity.y > 0.f) {
        //m velocity check
        if (this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;

        //Deceleration y positive
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0;
    } else if (this->velocity.y < 0.f) {
        if (this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;

        //Deceleration y negative
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0;
    }

    //Final move
    this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    //Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

const bool MovementComponent::getState(const MOVEMENT_STATES state) const {
    switch (state) {
        case MOVEMENT_STATES::IDLE:
            return this->velocity.x == 0.f && this->velocity.y == 0.f;
        case MOVEMENT_STATES::MOVING:
            return (this->velocity.x != 0.f || this->velocity.y != 0.f);
        case MOVEMENT_STATES::MOVING_LEFT:
            return (this->velocity.x < 0.f);
        case MOVEMENT_STATES::MOVING_RIGHT:
            return (this->velocity.x > 0.f);
        case MOVEMENT_STATES::MOVING_UP:
            return (this->velocity.y > 0.f);
        case MOVEMENT_STATES::MOVING_DOWN:
            return (this->velocity.y < 0.f);
    }
    return false;
}

float MovementComponent::getMaxVelocity() const {
    return maxVelocity;
}


