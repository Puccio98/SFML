#ifndef SFML_ENEMYSPAWNER_H
#define SFML_ENEMYSPAWNER_H


#include <System/Vector2.hpp>
#include "../enums/enemy_types.cpp"
#include "../Entities/Enemy.h"


class EnemySpawner {
private:
    ENEMY type;
    EntityDimensionData edd;
    int amount;
    int timeToSpawn;
    float maxDistance;
    /**
     * Renderizza lo spawner solamente in EditorState
     */
    bool show = false;

    sf::RectangleShape shape;
public:
    EnemySpawner(EntityDimensionData edd, ENEMY type, int amount, int timeToSpawn, float maxDistance);

    virtual ~EnemySpawner();

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void spawn();

    void clear();
};


#endif //SFML_ENEMYSPAWNER_H
