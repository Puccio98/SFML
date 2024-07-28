#include "EnemySpawner.h"

#include <utility>


EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : Tile(std::move(tileData), texture, font, hud), edd(edd), type(type), amount(amount), maxDistance(maxDistance),
          timeToSpawn(timeToSpawn) {
    this->shape.setSize(edd.size.getSize());
    this->shape.setPosition(edd.position);
    this->shape.setFillColor(sf::Color(206, 231, 24, 200));
}

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : EnemySpawner(std::move(tileData), texture, font, false, edd, type, amount, timeToSpawn, maxDistance) {
}


void EnemySpawner::render(sf::RenderTarget &target) {

}

void EnemySpawner::update() {

}

void EnemySpawner::spawn() {

}

void EnemySpawner::clear() {

}
