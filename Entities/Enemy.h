#ifndef SFML_ENEMY_H
#define SFML_ENEMY_H

#include "Entity.h"
#include "../Map/Tilemap.h"

class Enemy : public Entity {
private:
    void initVariables();

    void initAnimations();


public:
    Enemy(float x, float y, sf::Texture &texture_sheet, Tilemap &map);

    void render(sf::RenderTarget &target) override;

    void update(const float &dt) override;

    void update(const MovementData &md, const float &dt) override;

    void updateAnimation(const float &dt);

    ~Enemy() override;
};


#endif //SFML_ENEMY_H
