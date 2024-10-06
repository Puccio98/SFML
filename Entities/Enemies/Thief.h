#ifndef SFML_THIEF_H
#define SFML_THIEF_H


#include "Enemy.h"

class Thief : public Enemy {
public:
    Thief(float x, float y, sf::Texture &textureSheet);

    ~Thief() override;

    void updateAnimation(const float &dt) override;

    void flipAnimation(std::optional<DIRECTIONS> dir);

    void initAnimationComponent() override;

    void initVariables();
};


#endif //SFML_THIEF_H
