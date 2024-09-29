#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
        : sprite(sprite) {
    offsetX = offset_x;
    offsetY = offset_y;
    this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineColor(sf::Color::Red);
    this->hitbox.setOutlineThickness(1.f);
}

HitboxComponent::~HitboxComponent() = default;

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitbox);
}

void HitboxComponent::update() {
    this->hitbox.setPosition(computePosition(this->sprite.getPosition()));
}

bool HitboxComponent::checkIntersect(const sf::FloatRect &frect) {
    return this->hitbox.getGlobalBounds().intersects(frect);
}

sf::Vector2f &HitboxComponent::getPosition() const {
    return const_cast<sf::Vector2f &>(this->hitbox.getPosition());
}

void HitboxComponent::setPosition(const sf::Vector2f &position) {
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

/**
 * A partire da una posizione (di uno sprite), calcola la posizione della relativa hitbox.
 * @param spritePosition
 * @return
 */
sf::Vector2f HitboxComponent::computePosition(sf::Vector2f spritePosition) const {
    return {spritePosition.x + this->offsetX,
            spritePosition.y + this->offsetY};
}

sf::RectangleShape HitboxComponent::getHitboxRectangleShapeFromPosition(sf::Vector2f spritePosition) const {
    sf::RectangleShape rectangleShape = sf::RectangleShape(this->hitbox.getSize());
    rectangleShape.setPosition(this->computePosition(spritePosition));
    return rectangleShape;
}

sf::Vector2f HitboxComponent::getSize() {
    return this->hitbox.getSize();
}

const sf::RectangleShape &HitboxComponent::getHitbox() const {
    return hitbox;
}
