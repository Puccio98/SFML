#include "EnemySpawner.h"


EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : Tile(std::move(tileData), texture, font, hud), edd(edd), type(type), counter(amount),
          maxDistance(maxDistance),
          timeToSpawn(timeToSpawn) {
    this->layerText.setString(this->layerText.getString() + ", es");
    this->layerText.setFillColor(sf::Color(200, 200, 30));
    this->shape.setSize(edd.size);
    this->shape.setPosition(edd.position);
}

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : EnemySpawner(std::move(tileData), texture, font, false, edd, type, amount, timeToSpawn, maxDistance) {
}


void EnemySpawner::render(sf::RenderTarget &target) {
    Tile::render(target);
}

void EnemySpawner::update(float dt) {
    Tile::update(dt);
    this->spawn();
}

void EnemySpawner::spawn() {
    if (this->counter < 1) {
        std::cout << "spawnato primo nemico" << std::endl;
        this->counter++;
    }
}

void EnemySpawner::clear() {

}
