#ifndef SFML_ENEMY_H
#define SFML_ENEMY_H

#include "../Entity.h"

class Enemy : public Entity {
private:
    void initVariables(std::pair<int, int> pair, std::pair<int, int> pair1);

    // Create a static clock to track the time
    sf::Clock clock;
public:
    Enemy(float x, float y, sf::Texture &texture_sheet, std::pair<int, int> sprite_dimension,
          std::pair<int, int> hitbox_dimension);

    void render(sf::RenderTarget &target) override;

    void update(const float &dt) override;

    void update(const MovementData &md, const float &dt) override;

    virtual void updateAnimation(const float &dt) = 0;

    ~Enemy() override;

    void updateDirections(const float &dt);

    virtual void initAnimationComponent() = 0;

    void initEnemyComponents(sf::Texture &texture);
};


#endif //SFML_ENEMY_H
