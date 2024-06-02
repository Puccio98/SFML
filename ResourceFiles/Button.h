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
        //TODO:: Creare struct per gestire triplette di colori e aggiungere outlineColor.
        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

    public:
        Button(float x, float y, float width, float height, sf::Font *font, std::string text,
               unsigned int character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
               sf::Color hover_color, sf::Color active_color, short unsigned id = 0);

        virtual ~Button();

        //Functions
        virtual void update(sf::Vector2f mousePos) = 0;

        void render(sf::RenderTarget &target);

        //Modifiers
        void setText(std::string text);

        //Accessors
        bool isPressed() const;

        std::string getText() const;

        virtual void handleEvent(sf::Event &event, sf::Vector2f mousePos) = 0;

        virtual void reset() = 0;

        unsigned short getId() const;
    };
}


#endif //SFML_BUTTON_H
