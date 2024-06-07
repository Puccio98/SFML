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
#include "CssColor.h"

enum button_states {
    BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE
};
namespace GUI {
    class Button {
    private:
        short unsigned id;
        sf::Font *font;

    protected:
        short unsigned buttonState;
        sf::Text text;
        sf::RectangleShape shape;
        CssColor textColor;
        CssColor buttonColor;
        bool locked = false;

    public:
        Button(float x, float y, float width, float height, sf::Font *font, const std::string &text,
               unsigned int character_size, const CssColor &text_color, const CssColor &button_color,
               short unsigned id);

        Button(float x, float y, float width, float height, sf::Font *font, const std::string &text,
               unsigned int character_size, const CssColor &text_color, const CssColor &button_color);

        virtual ~Button();

        //Functions
        virtual void update(sf::Vector2f mousePos) = 0;

        void render(sf::RenderTarget &target);

        //Modifiers
        void setText(std::string text);

        //Accessors
        bool isClicked() const;

        std::string getText() const;

        virtual void handleEvent(sf::Event &event, sf::Vector2f mousePos);

        void reset();

        unsigned short getId() const;
    };
}


#endif //SFML_BUTTON_H
