#ifndef SFML_FORESTGUY_H
#define SFML_FORESTGUY_H


#include "../Enemy.h"

class ForestGuy : public Enemy {
public:
    ForestGuy(float x, float y, sf::Texture &textureSheet);

    virtual ~ForestGuy();
};


#endif //SFML_FORESTGUY_H
