#include "EnemySpawner.h"


EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : Tile(std::move(tileData), texture, font, hud), edd(edd), type(type), counter(amount),
          maxDistance(maxDistance),
          timeToSpawn(timeToSpawn) {
    this->initTextures();
    this->layerText.setString(this->layerText.getString() + ", es");
    this->layerText.setFillColor(sf::Color(200, 200, 30));
    this->shape.setSize(edd.size);
    this->shape.setPosition(edd.position);
}

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                           EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance)
        : EnemySpawner(std::move(tileData), texture, font, false, edd, type, amount, timeToSpawn, maxDistance) {
}


void EnemySpawner::initTextures() {
    if (!this->textures["ENEMY_SHEET"].loadFromFile(
            "Resources/images/sprites/entities/enemies/wisp/test_walk_back.png")) {
        throw "ERROR::enemy_spawner::COULD_NOT_ENEMY_TEXTURE";
    }
}

void EnemySpawner::render(sf::RenderTarget &target) {
    Tile::render(target);
}

void EnemySpawner::update(float dt, std::vector<Enemy *> &enemies) {
    Tile::update(dt, enemies);
    this->spawn(enemies);
}

void EnemySpawner::spawn(std::vector<Enemy *> &enemies) {
    if (this->counter < 1) {
        std::cout << "spawnato primo nemico" << std::endl;
        enemies.push_back(
                new Enemy(this->tiledata.gridSize * this->tiledata.index_x,
                          this->tiledata.gridSize * this->tiledata.index_y,
                          this->textures["ENEMY_SHEET"])
        );

        this->counter++;
    }
}

void EnemySpawner::clear() {

}
