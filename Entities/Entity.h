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

    HitboxComponent *hitboxComponent;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;
public:
    Entity();

    virtual ~Entity();

    //Compoent Functons
    void setTexture(sf::Texture &texture);

    void createMovementComponent(float maxVelocity, float acceleration, float deceleration);

    void createAnimationComponent(sf::Texture &texture_sheet);

    void createHitboxComponent(sf::Sprite &_sprite, float offset_x, float offset_y, float width, float height);

    //Functions
    virtual void setPosition(float x, float y);

    virtual void move(sf::Vector2f direction, const float &dt);

    virtual void update(const float &dt);

    virtual void render(sf::RenderTarget &target);
};

#endif //SFML_ENTITY_H
