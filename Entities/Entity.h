#ifndef SFML_ENTITY_H
#define SFML_ENTITY_H

#include "Components/HitboxComponent.h"
#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/AttributeComponent.h"
#include "Components/SkillComponent.h"

class Entity {

private:
    void initVariables(std::pair<int, int> pair, std::pair<int, int> pair1);

protected:
    sf::Sprite sprite;
    std::pair<int, int> spriteDimension;
    std::pair<int, int> hitboxDimension;

    unsigned layerIndex = 0;
    HitboxComponent *hitboxComponent{};
    MovementComponent *movementComponent{};
    AnimationComponent *animationComponent{};
    AttributeComponent *attributeComponent{};
    SkillComponent *skillComponent{};

    void createHitboxComponent(float offset_x, float offset_y, float width, float height);

public:
    explicit Entity();

    unsigned int getLayer() const;

    virtual ~Entity();

    //Accessors
    HitboxComponent *getHitboxComponent() const;

    //Component Functons


    void createMovementComponent(float maxVelocity, float acceleration, float deceleration);

    void createAnimationComponent(sf::Texture &texture_sheet);

    void createSkillComponent();


    void createAttributeComponent();

    MovementComponent *getMovementComponent() const;

    //Functions
    virtual void setPosition(float x, float y);

    virtual const sf::Vector2f getHitboxPosition() const;

    virtual const sf::Vector2f getHitboxSize() const;

    virtual const sf::Vector2f getSpritePosition() const;

    virtual const sf::Vector2f getSpriteSize() const;

    virtual void setDirection(sf::Vector2f direction, const float &dt);

    virtual void update(const float &dt);

    virtual void update(const MovementData &md, const float &dt);

    virtual void render(sf::RenderTarget &target);

    AttributeComponent *getAttributeComponent() const;

    const sf::Sprite &getSprite() const;
};

#endif //SFML_ENTITY_H
