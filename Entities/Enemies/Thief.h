#pragma once

#include "Enemy.h"

class Thief : public Enemy {
public:
    Thief(float x, float y, sf::Texture &textureSheet);

    ~Thief() override;

    void updateAnimation(const float &dt) override;

    void initAnimationComponent() override;
};