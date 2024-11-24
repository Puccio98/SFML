#include "EnemySpawner.h"
#include "../../Entities/Enemies/Thief.h"
#include "../../Entities/Enemies/Wisp.h"
#include "EnemySpawnerData.h"


EnemySpawner::~EnemySpawner() = default;

EnemySpawner::EnemySpawner(EnemySpawnerData *enemySpawnerData, sf::Texture &texture, sf::Font &font, bool hud,
                           EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance)
        : MapObject(enemySpawnerData, hud), edd(edd), type(type), counter(amount),
          maxDistance(maxDistance),
          timeToSpawn(timeToSpawn) {
    this->initTextures();
}

EnemySpawner::EnemySpawner(EnemySpawnerData *enemySpawnerData, sf::Texture &texture, sf::Font &font,
                           EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance)
        : EnemySpawner(enemySpawnerData, texture, font, false, edd, type, amount, timeToSpawn, maxDistance) {
}


void EnemySpawner::initTextures() {
    std::string enemy_texture_path;
    switch (type) {
        case ENEMY_TYPES::WISP:
            enemy_texture_path = "Resources/images/sprites/entities/enemies/grim_reaper/16x16 Grim Reaper.png";
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
    MapObject::render(target);
}

void EnemySpawner::update(float dt, std::vector<Entity *> &entities) {
    MapObject::update(dt, entities);
    this->spawn(entities);
}

void EnemySpawner::spawn(std::vector<Entity *> &entities) {
    if (this->counter < 1) {
        Enemy *enemy;
        switch (type) {
            case ENEMY_TYPES::WISP:
                enemy = new Wisp(this->data->gridSize * this->data->index_x,
                                 this->data->gridSize * this->data->index_y,
                                 this->textures["ENEMY_SHEET"]);
                break;
            case ENEMY_TYPES::THIEF:
                enemy = new Thief(this->data->gridSize * this->data->index_x,
                                  this->data->gridSize * this->data->index_y,
                                  this->textures["ENEMY_SHEET"]);
                break;
            default:
                throw "ERROR::enemy_spawner::NOT_IMPLEMENTED";
        }

        entities.push_back(enemy);

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
