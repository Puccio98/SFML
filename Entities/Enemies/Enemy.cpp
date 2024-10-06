#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture &texture_sheet, std::pair<int, int> sprite_dimension,
             std::pair<int, int> hitbox_dimension) {
    this->initVariables(sprite_dimension, hitbox_dimension);
    this->setPosition(x, y);
    this->initEnemyComponents(texture_sheet);
}

Enemy::~Enemy() {

}

void Enemy::render(sf::RenderTarget &target) {
    Entity::render(target);
}


void Enemy::update(const float &dt) {
    // Se chiamato senza i dati del movimento li calcola autonomamente assumendo che possa muoversi in quelle direzioni/punti
    MovementData next = this->movementComponent->nextMovementData(dt);

    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Enemy::update(const MovementData &next, const float &dt) {
    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
    this->updateDirections(dt);
}

void Enemy::initVariables(std::pair<int, int> sprite_dimension, std::pair<int, int> hitbox_dimension) {
    this->spriteDimension = sprite_dimension;
    this->hitboxDimension = hitbox_dimension;
}

void Enemy::updateDirections(const float &dt) {
    // Get the elapsed time
    sf::Time elapsedTime = clock.getElapsedTime();

    // If 5 seconds have passed
    if (elapsedTime.asSeconds() >= 3.0f) {
        // Generate random directions (-1, 0, or 1) for both x and y
        int xDir = (rand() % 3) - 1; // Generates -1, 0, or 1
        int yDir = (rand() % 3) - 1; // Generates -1, 0, or 1

        // Set the new random direction
        this->movementComponent->setDirection(sf::Vector2f(xDir, yDir));

        // Restart the clock to measure the next 5 seconds
        clock.restart();
    }
}

void Enemy::initEnemyComponents(sf::Texture &texture) {
    this->createHitboxComponent(0, 0, this->hitboxDimension.first, this->hitboxDimension.second);
    this->createMovementComponent(100.f, 2000.f, 900.f);
    this->createAnimationComponent(texture);
    this->createAttributeComponent();
    this->createSkillComponent();
}
