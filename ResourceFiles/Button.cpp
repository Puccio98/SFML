#include "Button.h"

GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text,
                    unsigned character_size,
                    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                    sf::Color idle_color,
                    sf::Color hover_color, sf::Color active_color, short unsigned id) {
    this->id = id;
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
            this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f -
            this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f -
            this->text.getGlobalBounds().height / 2.f
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->shape.setFillColor((idle_color));
}

GUI::Button::~Button() {

}

void GUI::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}

bool GUI::Button::isPressed() const {
    return this->buttonState == BTN_ACTIVE;
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
