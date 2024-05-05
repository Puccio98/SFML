#include "MovementComponent.h"
#include <cmath>

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite), md(maxVelocity, acceleration, deceleration) {
}

MovementComponent::~MovementComponent() = default;

//Functions
void MovementComponent::update(const MovementData &next) {
    this->md = next;

    // Move player by delta position
    this->sprite.setPosition(this->md.position);
}

/**
 * Check that velocity doesn't exceed max speed
 */
void MovementComponent::checkVelocity(MovementData &_md) {
    double vx = std::abs(_md.velocity.x);
    double vy = std::abs(_md.velocity.y);
    double maxComponentVelocity = (_md.maxVelocity / std::sqrt(2));

    if (std::pow(vx, 2) + std::pow(vy, 2) > std::pow(_md.maxVelocity, 2)) {
        if (vx > maxComponentVelocity && vy > maxComponentVelocity) {
            vx = maxComponentVelocity;
            vy = maxComponentVelocity;
        } else if (vx <= vy) {
            vy = _md.maxVelocity - vx <= 0 ? std::sqrt(_md.maxVelocity) :
                 std::sqrt(std::pow(_md.maxVelocity, 2) - std::pow(vx, 2));
        } else {
            vx = _md.maxVelocity - vy <= 0 ? std::sqrt(_md.maxVelocity) :
                 std::sqrt(std::pow(_md.maxVelocity, 2) - std::pow(vy, 2));
        }
    }

    _md.velocity.x = float(vx * _md.direction.x);
    _md.velocity.y = float(vy * _md.direction.y);
}

void MovementComponent::handleFriction(MovementData &_md, const float &dt) {// Handle player friction
    float deceleration_dt = _md.deceleration * dt;
    if (_md.velocity.x != 0) {
        float velocity_friction = (-1.f * (_md.velocity.x / std::abs(_md.velocity.x))) * deceleration_dt;
        _md.velocity.x =
                std::abs(velocity_friction) > std::abs(_md.velocity.x) ? 0 : _md.velocity.x + velocity_friction;
    }
    if (_md.velocity.y != 0) {
        float velocity_friction = (-1.f * (_md.velocity.y / std::abs(_md.velocity.y))) * deceleration_dt;
        _md.velocity.y =
                std::abs(velocity_friction) > std::abs(_md.velocity.y) ? 0 : _md.velocity.y + velocity_friction;
    }
}

void MovementComponent::setDirection(sf::Vector2f _direction) {
    this->md.direction = _direction;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->md.velocity;
}

bool MovementComponent::getState(const MOVEMENT_STATES state) const {
    switch (state) {
        case MOVEMENT_STATES::IDLE:
            return (this->md.velocity.x == 0.f && this->md.velocity.y == 0.f);
        case MOVEMENT_STATES::MOVING:
            return (this->md.velocity.x != 0.f || this->md.velocity.y != 0.f);
        case MOVEMENT_STATES::MOVING_LEFT:
            return (this->md.velocity.x < 0.f);
        case MOVEMENT_STATES::MOVING_RIGHT:
            return (this->md.velocity.x > 0.f);
        case MOVEMENT_STATES::MOVING_UP:
            return (this->md.velocity.y > 0.f);
        case MOVEMENT_STATES::MOVING_DOWN:
            return (this->md.velocity.y < 0.f);
    }
    return false;
}

float MovementComponent::getMaxVelocity() const {
    return this->md.maxVelocity;
}

__attribute__((unused)) void MovementComponent::debugVelocity() const {
    std::cout << "vx: " << this->md.velocity.x << "\n";
    std::cout << "vy: " << this->md.velocity.y << "\n";
}

float MovementComponent::getVelocityMagnitude() const {
    return float(std::sqrt(std::pow(this->md.velocity.x, 2) + std::pow(this->md.velocity.y, 2)));
}

/**
 * Ricava le informazioni su posizione, velocita e accelerazione per il movimento del prossimo frame
 * @param dt
 * @return
 */
MovementData MovementComponent::nextMovementData(const float &dt) {
    //Create Movement data clone
    MovementData next(this->md);

    // Create acceleration vector
    sf::Vector2f accelerationV = next.direction.x != 0 && next.direction.y != 0 ? sf::Vector2f(
            next.direction * float(next.acceleration / std::sqrt(2))) : sf::Vector2f(
            next.direction * next.acceleration);

    // Apply acceleration on current velocity
    next.velocity += (accelerationV) * dt;

    // Handle terrain friction
    handleFriction(next, dt);

    // Check maximum speed
    checkVelocity(next);

    // Setta la posizione calcolate tutti i vettori del movimento
    next.position = next.position + (next.velocity * dt);

    return next;
}
