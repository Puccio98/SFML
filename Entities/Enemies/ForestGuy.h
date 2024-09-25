#ifndef SFML_FORESTGUY_H
#define SFML_FORESTGUY_H


#include "Enemy.h"

class ForestGuy : public Enemy {
public:
    ForestGuy(float x, float y, sf::Texture &textureSheet);

    virtual ~ForestGuy();

    void updateAnimation(const float &dt) override;

    void initAnimationComponent() override;
};


#endif //SFML_FORESTGUY_H
