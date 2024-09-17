#include "MovementComponent.h"
#include <cmath>

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite), md(maxVelocity, acceleration, deceleration, sprite.getPosition()) {
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

    if (_md.velocity.x != 0) {
        _md.velocity.x = float(vx * (_md.velocity.x / std::abs(_md.velocity.x)));
    }
    if (_md.velocity.y != 0) {
        _md.velocity.y = float(vy * ((_md.velocity.y / std::abs(_md.velocity.y))));
    }
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
    this->md.accelerationDirection = _direction;
}

const MovementData &MovementComponent::getMovementData() const {
    return md;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->md.velocity;
}

bool MovementComponent::isState(MOVEMENT_STATES state) const {
    switch (state) {
        case MOVEMENT_STATES::IDLE:
            return (this->md.velocity.x == 0.f && this->md.velocity.y == 0.f);
        case MOVEMENT_STATES::MOVING:
            return (this->md.velocity.x != 0.f || this->md.velocity.y != 0.f);
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
MovementData MovementComponent::nextMovementData(const float &dt,
                                                 std::tuple<bool, bool> forbidden_directions) const {
    // Create Movement data clone
    MovementData next(this->md);

    if (std::get<0>(forbidden_directions)) {
        next.accelerationDirection.x = 0;
        // Se non puoi muoverti in quella direzione azzera la velocità per evitare che il tempo di decelerazione ti faccia andare dove non puoi
        next.velocity.x = 0;
    }

    if (std::get<1>(forbidden_directions)) {
        next.accelerationDirection.y = 0;
        // Se non puoi muoverti in quella direzione azzera la velocità per evitare che il tempo di decelerazione ti faccia andare dove non puoi
        next.velocity.y = 0;
    }
    return computeNextMovementData(dt, next);
}

MovementData
MovementComponent::computeNextMovementData(const float &dt, MovementData next) {
    // Aggiorno facing direction
    next = updateFacingDirection(next);

    // Create acceleration vector
    auto accelerationV = sf::Vector2f(next.accelerationDirection * next.acceleration);

    // Apply acceleration on current velocity
    next.velocity = next.velocity + ((accelerationV) * dt);

    // Handle terrain friction
    handleFriction(next, dt);

    // Check maximum speed
    checkVelocity(next);

    // Setta la posizione calcolate tutti i vettori del movimento
    next.position = next.position + (next.velocity * dt);

    return next;
}

MovementData &MovementComponent::updateFacingDirection(MovementData &next) {
    if (next.velocity.x == 0) {
        next.facingDirection.first = std::nullopt;
    }

    if (next.velocity.y != 0) {
        next.facingDirection.second = next.velocity.y > 0 ? DIRECTIONS::DOWN : DIRECTIONS::UP;
    }

    if (next.velocity.x != 0) {
        next.facingDirection.first = next.velocity.x > 0 ? DIRECTIONS::RIGHT : DIRECTIONS::LEFT;
    }

    return next;
}

MovementData MovementComponent::nextMovementData(const float &dt) const {
    //Create Movement data clone
    MovementData next(this->md);
    return computeNextMovementData(dt, next);
}

