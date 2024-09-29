#ifndef SFML_ENTITY_H
#define SFML_ENTITY_H

#include "Components/HitboxComponent.h"
#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/AttributeComponent.h"
#include "Components/SkillComponent.h"

class Entity {

private:
    void initVariables();

protected:
    sf::Sprite sprite;

    unsigned layerIndex = 0;
    HitboxComponent *hitboxComponent{};
    MovementComponent *movementComponent{};
    AnimationComponent *animationComponent{};
    AttributeComponent *attributeComponent{};
    SkillComponent *skillComponent{};
public:
    explicit Entity();

    unsigned int getLayer() const;

    virtual ~Entity();

    //Accessors
    HitboxComponent *getHitboxComponent() const;

    //Compoent Functons


    void createMovementComponent(float maxVelocity, float acceleration, float deceleration);

    void createAnimationComponent(sf::Texture &texture_sheet);

    void createSkillComponent();

    void createHitboxComponent(float offset_x, float offset_y, float width, float height);

    void createAttributeComponent();

    MovementComponent *getMovementComponent() const;

    //Functions
    virtual void setPosition(float x, float y);

    virtual const sf::Vector2f getPosition() const;

    virtual const sf::Vector2f getSize() const;

    virtual void setDirection(sf::Vector2f direction, const float &dt);

    virtual void update(const float &dt);

    virtual void update(const MovementData &md, const float &dt);

    virtual void render(sf::RenderTarget &target);

    AttributeComponent *getAttributeComponent() const;

    const sf::Sprite &getSprite() const;
};

#endif //SFML_ENTITY_H
