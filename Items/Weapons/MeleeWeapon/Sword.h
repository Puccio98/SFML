#pragma once

#include "MeleeWeapon.h"

class Sword : public MeleeWeapon {
public:
    Sword();

    ~Sword() override;

    void update(const sf::Vector2f &position, std::pair<std::optional<DIRECTIONS>, DIRECTIONS> facingDirection, std::string animation, const float &dt) override;

    void update(const sf::Vector2f &position, std::pair<std::optional<DIRECTIONS>, DIRECTIONS> facingDirection, const float &dt) override;

    void render(sf::RenderTarget &target) override;

private:
    void initVariables();

    void initAnimationComponent();

    void updateAnimation(const float &dt) override;

    void initHitboxComponent();

public:

private:
};

