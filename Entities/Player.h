#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    //Variables

    //Initializer Functions
    void initVariables();

public:
    Player(float x, float y, sf::Texture& texture_sheet);

    virtual ~Player();

    //Functions
    void update(const float& dt) override;

};


#endif //SFML_PLAYER_H
