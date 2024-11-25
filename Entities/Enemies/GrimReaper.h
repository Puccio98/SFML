#pragma once

#include "Enemy.h"

class GrimReaper : public Enemy {
public:
    GrimReaper(float x, float y, sf::Texture &textureSheet);

    ~GrimReaper() override;

    void updateAnimation(const float &dt) override;

    void initAnimationComponent() override;
};