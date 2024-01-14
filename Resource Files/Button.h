#ifndef SFML_BUTTON_H
#define SFML_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
    short unsigned buttonState;
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned int character_size,
           sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
           sf::Color hover_color, sf::Color active_color);

    virtual ~Button();

    //Functions
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget &target);

    //Accessors
    bool isPressed() const;
};


#endif //SFML_BUTTON_H
