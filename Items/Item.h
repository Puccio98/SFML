#ifndef SFML_ITEM_H
#define SFML_ITEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>
#include "../Entities/Components/AnimationComponent.h"
#include "../Entities/Components/HitboxComponent.h"

class Item {
private:
protected:
    sf::Vector2f offset;
    sf::Vector2i dimensions;
    AnimationComponent *animationComponent{};
    HitboxComponent *hitboxComponent{};

public:
    Item();

    virtual ~Item();

    virtual void update(const sf::Vector2f &position, const float &dt) = 0;

    virtual void render(sf::RenderTarget &target) = 0;

    virtual void updateAnimation(const float &dt) = 0;

};


#endif //SFML_ITEM_H
