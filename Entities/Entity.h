#ifndef SFML_ENTITY_H
#define SFML_ENTITY_H

#include "Components/HitboxComponent.h"
#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"


class Entity {

private:
    void initVariables();

protected:
    sf::Sprite sprite;

    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
public:
    Entity();

    virtual ~Entity();

    //Compoent Functons
    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture & texture_sheet);
    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

    //Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(float x, float y, const float &dt);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget &target);
};

#endif //SFML_ENTITY_H
