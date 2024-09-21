#ifndef SFML_ENEMYSPAWNER_H
#define SFML_ENEMYSPAWNER_H


#include <System/Vector2.hpp>
#include "Enemies/Enemy.h"
#include "EntityDimensionData.h"
#include "../Tile/Tile.h"
#include <utility>


class EnemySpawner : public Tile {
private:
    ENEMY_TYPES type;
    EntityDimensionData edd;
    int counter;
    int timeToSpawn;
    float maxDistance;
    sf::RectangleShape shape;
    std::map<std::string, sf::Texture> textures;

    std::string getEnemyName();

public:
    EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud,
                 EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance);

    EnemySpawner(TileData tileData, sf::Texture &texture, sf::Font &font,
                 EntityDimensionData edd, ENEMY_TYPES type, int amount, int timeToSpawn, float maxDistance);

    virtual ~EnemySpawner();

    void update(float dt, std::vector<Enemy *> &enemies) override;

    void render(sf::RenderTarget &target) override;

    void spawn(std::vector<Enemy *> &enemies);

    void clear();

    void initTextures();
};


#endif //SFML_ENEMYSPAWNER_H
