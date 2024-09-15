#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);

    this->createHitboxComponent(0, 0, 51, 72);
    this->createMovementComponent(100.f, 2000.f, 900.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent();
    this->createSkillComponent();

    this->animationComponent->addAnimation("IDLE", 5.f, 0, 0, 3, 0, 51, 72);
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
//    std::cout << "velocita x " << this->movementComponent->getVelocity().x << std::endl;
//    std::cout << "velocita y " << this->movementComponent->getVelocity().y << std::endl;
}

void Enemy::updateAnimation(const float &dt) {
    // Play the idle animation
    this->animationComponent->play("IDLE", dt);
}

void Enemy::initVariables() {

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

        std::cout << "dir x " << this->movementComponent->getMovementData().accelerationDirection.x << std::endl;
        std::cout << "dir y " << this->movementComponent->getMovementData().accelerationDirection.y << std::endl;
    }
}
