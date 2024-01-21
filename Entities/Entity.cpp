#include "Entity.h"

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

void Entity::move(sf::Vector2f direction, const float &dt) {
    if (this->movementComponent) {
        this->movementComponent->setDirection(direction); //Sets velocity, rename function
    }
}

void Entity::update(const float &dt) {

}

void Entity::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
    if (this->hitboxComponent)
        this->hitboxComponent->render(target);
}

//Functions
void Entity::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
    // togli
    this->sprite.setScale(0.2, 0.2);
}

void Entity::initVariables() {
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite &_sprite, float offset_x, float offset_y, float width, float height) {
    this->hitboxComponent = new HitboxComponent(_sprite, offset_x, offset_y, width, height);
}


