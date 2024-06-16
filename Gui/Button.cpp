#include "Button.h"
#include "CssColor.h"


GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                    unsigned int character_size, const CssColor &text_color, const CssColor &button_color,
                    short unsigned id) : id(id), textColor(text_color), buttonColor(button_color) {
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(this->textColor.idle);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
            this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f -
            this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f -
            this->text.getGlobalBounds().height / 2.f
    );

    this->shape.setFillColor((this->buttonColor.idle));
}

// Costruttore senza ID
GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                    unsigned int character_size, const CssColor &text_color, const CssColor &button_color)
        : Button(x, y, width, height, font, text, character_size, text_color, button_color, 0) {
}


GUI::Button::~Button() {

}

void GUI::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}

bool GUI::Button::isClicked() {
    bool _isClicked = this->clicked;
    this->clicked = false;
    return _isClicked;
}

std::string GUI::Button::getText() const {
    return this->text.getString();
}

void GUI::Button::setText(const std::string text) {
    this->text.setString(text);
}

unsigned short GUI::Button::getId() const {
    return id;
}

void GUI::Button::handleEvent(sf::Event &event, sf::Vector2f mousePos) {
    if (this->shape.getGlobalBounds().contains(mousePos) &&
        event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        this->clicked = true;
    } else {
        this->clicked = false;
    }
    /* this->clicked = this->shape.getGlobalBounds().contains(mousePos) &&
                    event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;*/

}
