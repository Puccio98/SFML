#include "MovementComponent.h"
#include <cmath>

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {
}

MovementComponent::~MovementComponent() = default;

//Functions
void MovementComponent::update(const float &dt) {
    // Create acceleration vector
    sf::Vector2f accelerationV = direction.x != 0 && direction.y != 0 ? sf::Vector2f(
            this->direction * float(this->acceleration / std::sqrt(2))) : sf::Vector2f(
            this->direction * this->acceleration);

    // Apply acceleration on current velocity
    this->velocity += (accelerationV) * dt;

    // Handle terrain friction
    this->handleFriction(dt);

    // Check maximum speed
    this->checkVelocity();

    // Move player by delta position
    this->sprite.move(this->velocity * dt);
}

/**
 * Check that velocity doesn't exceed max speed
 */
void MovementComponent::checkVelocity() {
    double vx = std::abs(velocity.x);
    double vy = std::abs(velocity.y);
    double maxComponentVelocity = (maxVelocity / std::sqrt(2));

    if (std::pow(vx, 2) + std::pow(vy, 2) > std::pow(maxVelocity, 2)) {
        if (vx > maxComponentVelocity && vy > maxComponentVelocity) {
            vx = maxComponentVelocity;
            vy = maxComponentVelocity;
        } else if (vx <= vy) {
            vy = maxVelocity - vx <= 0 ? std::sqrt(maxVelocity) :
                 std::sqrt(std::pow(maxVelocity, 2) - std::pow(vx, 2));
        } else {
            vx = maxVelocity - vy <= 0 ? std::sqrt(maxVelocity) :
                 std::sqrt(std::pow(maxVelocity, 2) - std::pow(vy, 2));
        }
    }

    velocity.x = float(vx * direction.x);
    velocity.y = float(vy * direction.y);
}

void MovementComponent::handleFriction(const float &dt) {// Handle player friction
    float deceleration_dt = deceleration * dt;
    if (velocity.x != 0) {
        float velocity_friction = (-1.f * (velocity.x / std::abs(velocity.x))) * deceleration_dt;
        velocity.x = std::abs(velocity_friction) > std::abs(velocity.x) ? 0 : velocity.x + velocity_friction;
    }
    if (velocity.y != 0) {
        float velocity_friction = (-1.f * (velocity.y / std::abs(velocity.y))) * deceleration_dt;
        velocity.y = std::abs(velocity_friction) > std::abs(velocity.y) ? 0 : velocity.y + velocity_friction;
    }
}

void MovementComponent::setDirection(sf::Vector2f _direction) {
    this->direction = _direction;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

bool MovementComponent::getState(const MOVEMENT_STATES state) const {
    switch (state) {
        case MOVEMENT_STATES::IDLE:
            return (this->velocity.x == 0.f && this->velocity.y == 0.f);
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

__attribute__((unused)) void MovementComponent::debugVelocity() const {
    std::cout << "vx: " << velocity.x << "\n";
    std::cout << "vy: " << velocity.y << "\n";
}

float MovementComponent::getVelocityMagnitude() const {
    return float(std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2)));
}