#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include "Entity.h"
#include "../Map/Tilemap.h"

class Player final : public Entity {
private:
    //Variables
    Tilemap &map;

    //Initializer Functions
    void initVariables();

public:
    Player(float x, float y, sf::Texture &texture_sheet, Tilemap &map);

    ~Player() final;

    //Functions
    void update(const float &dt) override;

    void update(const MovementData &next, const float &dt) override;

    void attack(const float &dt);

    void updateAnimation(const float &dt);

    float getCurrentHp();

    float getMaxHp();
};


#endif //SFML_PLAYER_H
