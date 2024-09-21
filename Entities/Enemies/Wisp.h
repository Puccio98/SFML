#ifndef SFML_WISP_H
#define SFML_WISP_H


#include "Enemy.h"

class Wisp : public Enemy {
public:
    Wisp(float x, float y, sf::Texture &textureSheet);

    ~Wisp() override;

    void updateAnimation(const float &dt) override;

    void initAnimationComponent() override;
};


#endif //SFML_WISP_H
