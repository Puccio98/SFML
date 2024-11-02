#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include "Entity.h"
#include "../Items/Weapons/MeleeWeapon/Sword.h"
#include "../enums/player_animations.cpp"
#include "../enums/player_actions.cpp"

class Player final : public Entity {
private:
    Weapon *weapon = new Sword();
    float invincibilityDuration;
    sf::Clock invincibilityClock;
    PLAYER_ANIMATIONS nextAnimation;
    std::set<PLAYER_ACTIONS> playerActions;

    //Initializer Functions
    void initVariables(std::pair<int, int> pair, std::pair<int, int> pair1);

    void updateInternal(const MovementData &next, const float &dt);

public:

    Player(float x, float y, sf::Texture &texture_sheet);

    ~Player() final;

    //Functions
    void update(const float &dt) override;

    void update(const MovementData &next, const float &dt) override;

    void render(sf::RenderTarget &target);

    void attack();

    void setNextAnimation(const float &dt);

    float getCurrentHp();

    float getMaxHp();

    void flipAnimation(std::optional<DIRECTIONS> dir);

    bool isInvincible() const;

    void takeDamage();

    std::string getAnimationKey(PLAYER_ANIMATIONS animation);

    const Weapon *getWeapon() const;

    const std::set<PLAYER_ACTIONS> &getPlayerActions() const {
        return playerActions;
    }

    bool isPlayerAttacking();
};


#endif //SFML_PLAYER_H
