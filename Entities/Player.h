#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include "Entity.h"
#include "../Map/Tilemap.h"

class Player : public Entity {
private:
    //Variables
    Tilemap &map;


    //Initializer Functions
    void initVariables();

public:
    Player(float x, float y, sf::Texture &texture_sheet, Tilemap &map);

    virtual ~Player();

    //Functions
    void update(const float &dt) override;

    void attack(const float &dt);
};


#endif //SFML_PLAYER_H
