#include "Entity.h"

Entity::Entity() {
    this->initVariables(std::pair<int, int>(), std::pair<int, int>());
}

Entity::~Entity() {
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->attributeComponent;
    delete this->skillComponent;
}

void Entity::setDirection(sf::Vector2f direction, const float &dt) {
    if (this->movementComponent) {
        this->movementComponent->setDirection(direction);
    }
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


void Entity::initVariables(std::pair<int, int> pair, std::pair<int, int> pair1) {
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
    this->attributeComponent = nullptr;
    this->skillComponent = nullptr;
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(float offset_x, float offset_y, float width, float height) {
    this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createSkillComponent() {
    this->skillComponent = new SkillComponent();
}

const sf::Vector2f Entity::getPosition() const {
    return this->hitboxComponent->getPosition();
}

const sf::Vector2f Entity::getSize() const {
    return this->hitboxComponent->getSize();
}

MovementComponent *Entity::getMovementComponent() const {
    return movementComponent;
}

void Entity::update(const MovementData &md, const float &dt) {

}

void Entity::update(const float &dt) {

}

HitboxComponent *Entity::getHitboxComponent() const {
    return hitboxComponent;
}

unsigned int Entity::getLayer() const {
    return layerIndex;
}

void Entity::createAttributeComponent() {
    this->attributeComponent = new AttributeComponent();
}

AttributeComponent *Entity::getAttributeComponent() const {
    return attributeComponent;
}

const sf::Sprite &Entity::getSprite() const {
    return sprite;
}



