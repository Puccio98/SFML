#include "PushButton.h"

GUI::PushButton::PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                            unsigned int characterSize, const CssColor &text_color, const CssColor &button_color,
                            unsigned short id) :
        Button(x, y, width, height, font, text, characterSize, text_color, button_color, id){}

GUI::PushButton::PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                            unsigned int characterSize, const CssColor &text_color, const CssColor &button_color)
        : PushButton(x, y, width, height, font, text, characterSize, text_color, button_color, 0) {}


void GUI::PushButton::update(sf::Vector2f mousePos) {
    this->buttonState = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;

        // Pressed
        if (this->locked) {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState) {
        case BTN_IDLE:
            this->shape.setFillColor(this->buttonColor.idle);
            this->text.setFillColor(this->textColor.idle);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->buttonColor.hover);
            this->text.setFillColor(this->textColor.hover);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->buttonColor.active);
            this->text.setFillColor(this->textColor.active);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::White);
    }
}

GUI::PushButton::~PushButton() {

}
