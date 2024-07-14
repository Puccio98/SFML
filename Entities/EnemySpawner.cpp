#include "EnemySpawner.h"


EnemySpawner::~EnemySpawner() {

}

EnemySpawner::EnemySpawner(EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : edd(edd), type(type), amount(amount), maxDistance(maxDistance), timeToSpawn(timeToSpawn) {
    this->shape.setSize(edd.size.getSize());
    this->shape.setPosition(edd.position);
    this->shape.setFillColor(sf::Color(206, 231, 24, 200));

}

void EnemySpawner::render(sf::RenderTarget &target) {

}

void EnemySpawner::update(const float &dt) {

}

void EnemySpawner::spawn() {

}

void EnemySpawner::clear() {

}
