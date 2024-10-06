#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include "Entity.h"
#include "../Items/Weapons/MeleeWeapon/Sword.h"

class Player final : public Entity {
private:
    Sword sword;
    float invincibilityDuration;
    sf::Clock invincibilityClock;

    //Initializer Functions
    void initVariables(std::pair<int, int> pair, std::pair<int, int> pair1);

public:
    Player(float x, float y, sf::Texture &texture_sheet);

    ~Player() final;

    //Functions
    void update(const float &dt) override;

    void update(const MovementData &next, const float &dt) override;

    void render(sf::RenderTarget &target);

    void attack(const float &dt);

    void updateAnimation(const float &dt);

    float getCurrentHp();

    float getMaxHp();

    void flipAnimation(std::optional<DIRECTIONS> dir);

    bool isInvincible() const;

    void takeDamage();
};


#endif //SFML_PLAYER_H
