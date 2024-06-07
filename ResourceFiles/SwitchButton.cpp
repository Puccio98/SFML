//
// Created by malte on 02/06/2024.
//

#include "SwitchButton.h"

GUI::SwitchButton::SwitchButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                                unsigned int characterSize, const CssColor &text_color, const CssColor &button_color,
                                unsigned short id) : Button(x, y, width, height, font, text, characterSize, text_color,
                                                            button_color, id) {
    this->shape.setOutlineThickness(1.f);

}

GUI::SwitchButton::SwitchButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                                unsigned int characterSize, const CssColor &text_color, const CssColor &button_color)
        : SwitchButton(x, y, width, height, font, text, characterSize, text_color, button_color, 0) {

}

GUI::SwitchButton::~SwitchButton() = default;

void GUI::SwitchButton::update(sf::Vector2f mousePos) {

    // Hover
    if (this->active) {
        this->buttonState = BTN_ACTIVE;
    } else {
        this->buttonState = this->shape.getGlobalBounds().contains(mousePos) ? BTN_HOVER : BTN_IDLE;
    }
    this->shape.setOutlineColor(sf::Color::Transparent);

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
            this->shape.setOutlineColor(sf::Color::Green);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::White);
    }
}

void GUI::SwitchButton::handleEvent(sf::Event &event, sf::Vector2f mousePos) {
    if (this->shape.getGlobalBounds().contains(mousePos) &&
        event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        this->active = !this->active;
    }
}

bool GUI::SwitchButton::isActive() const {
    return active;
}
