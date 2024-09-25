#ifndef SFML_ENEMY_H
#define SFML_ENEMY_H

#include "../Entity.h"

class Enemy : public Entity {
private:
    void initVariables();

    // Create a static clock to track the time
    sf::Clock clock;
public:
    Enemy(float x, float y, sf::Texture &texture_sheet);

    void render(sf::RenderTarget &target) override;

    void update(const float &dt) override;

    void update(const MovementData &md, const float &dt) override;

    virtual void updateAnimation(const float &dt) = 0;

    ~Enemy() override;

    void updateDirections(const float &dt);

    virtual void initAnimationComponent() = 0;
};


#endif //SFML_ENEMY_H
