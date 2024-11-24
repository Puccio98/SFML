#pragma once

#include <System/Vector2.hpp>
#include "../../Entities/Enemies/Enemy.h"
#include "../../Entities/EntityDimensionData.h"
#include "../Tile/Tile.h"
#include "EnemySpawnerData.h"
#include <utility>

class EnemySpawner : public MapObject {
private:
    ENEMY_TYPES type;
    EntityDimensionData edd;
    int counter;
    int timeToSpawn;
    float maxDistance;
    std::map<std::string, sf::Texture> textures;

    std::string getEnemyName();

public:
    EnemySpawner(EnemySpawnerData *enemySpawnerData, sf::Texture &texture, sf::Font &font, bool hud,
                 EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance);

    EnemySpawner(EnemySpawnerData *enemySpawnerData, sf::Texture &texture, sf::Font &font,
                 EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance);

    virtual ~EnemySpawner();

    void update(float dt, std::vector<Entity *> &entities) override;

    void render(sf::RenderTarget &target) override;

    void spawn(std::vector<Entity *> &entities);

    void clear();

    void initTextures();
};