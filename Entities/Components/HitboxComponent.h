#ifndef SFML_HITBOXCOMPONENT_H
#define SFML_HITBOXCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>

class HitboxComponent {
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;

    float offsetX;
    float offsetY;

public:
    HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

    //Function
    bool checkIntersect(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget &target);
};

#endif //SFML_HITBOXCOMPONENT_H
