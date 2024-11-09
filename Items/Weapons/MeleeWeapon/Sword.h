#pragma once

#include "MeleeWeapon.h"

class Sword : public MeleeWeapon {
public:
    Sword();

    ~Sword() override;

    void update(const sf::Vector2f &position, std::string animation, const float &dt) override;

    void update(const sf::Vector2f &position, const float &dt) override;

    void render(sf::RenderTarget &target) override;

private:
    void initVariables();

    void initAnimationComponent();

    void updateAnimation(const float &dt) override;

    void initHitboxComponent();

public:

private:
    void flipAnimation();
};

