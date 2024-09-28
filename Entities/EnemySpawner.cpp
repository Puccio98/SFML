#include "EnemySpawner.h"
#include "Enemies/Thief.h"
#include "Enemies/Wisp.h"


EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                           EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance)
        : Tile(std::move(tileData), texture, font, hud), edd(edd), type(type), counter(amount),
          maxDistance(maxDistance),
          timeToSpawn(timeToSpawn) {
    this->initTextures();
    this->layerText.setString(this->layerText.getString() + "\n" + this->getEnemyName());
    this->layerText.setFillColor(sf::Color(200, 200, 30));
    this->shape.setSize(edd.size);
    this->shape.setPosition(edd.position);
}

EnemySpawner::EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                           EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance)
        : EnemySpawner(std::move(tileData), texture, font, false, edd, type, amount, timeToSpawn, maxDistance) {
}


void EnemySpawner::initTextures() {
    std::string enemy_texture_path;
    switch (type) {
        case ENEMY_TYPES::WISP:
            enemy_texture_path = "Resources/images/sprites/entities/enemies/wisp/wisp_sheet_x3.png";
            break;
        case ENEMY_TYPES::THIEF:
            enemy_texture_path = "Resources/images/sprites/entities/enemies/thief/thief_sheet_x3.png";
            break;
        default:
            throw "ERROR::enemy_spawner::NOT_IMPLEMENTED";
    }

    // Carica la texture
    if (!this->textures["ENEMY_SHEET"].loadFromFile(enemy_texture_path)) {
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
        Enemy *enemy;
        switch (type) {
            case ENEMY_TYPES::WISP:
                enemy = new Wisp(this->tiledata.gridSize * this->tiledata.index_x,
                                 this->tiledata.gridSize * this->tiledata.index_y,
                                 this->textures["ENEMY_SHEET"]);
                break;
            case ENEMY_TYPES::THIEF:
                enemy = new Thief(this->tiledata.gridSize * this->tiledata.index_x,
                                      this->tiledata.gridSize * this->tiledata.index_y,
                                      this->textures["ENEMY_SHEET"]);
                break;
            default:
                throw "ERROR::enemy_spawner::NOT_IMPLEMENTED";
        }

        enemies.push_back(enemy);

        this->counter++;
    }
}

std::string EnemySpawner::getEnemyName() {
    std::string enemyName;
    switch (this->type) {
        case ENEMY_TYPES::WISP:
            enemyName = "wisp";
            break;
        case ENEMY_TYPES::THIEF:
            enemyName = "thief";
            break;
    }
    return enemyName;
}

void EnemySpawner::clear() {

}
