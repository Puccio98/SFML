#ifndef SFML_ENEMYSPAWNER_H
#define SFML_ENEMYSPAWNER_H


#include <System/Vector2.hpp>
#include "../enums/enemy_types.cpp"
#include "../Entities/Enemy.h"
#include "EntityDimensionData.h"
#include "../Tile/Tile.h"
#include <utility>


class EnemySpawner : public Tile {
private:
    ENEMY type;
    EntityDimensionData edd;
    int amount;
    int timeToSpawn;
    float maxDistance;
    sf::RectangleShape shape;
public:
    EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                 EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance);

    EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                 EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance);

    virtual ~EnemySpawner();

    void update() override;

    void render(sf::RenderTarget &target) override;

    void spawn();

    void clear();
};


#endif //SFML_ENEMYSPAWNER_H
