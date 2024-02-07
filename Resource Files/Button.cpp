#include "Button.h"

GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text,
                    unsigned character_size,
                    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                    sf::Color idle_color,
                    sf::Color hover_color, sf::Color active_color) {
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

void GUI::Button::update(const sf::Vector2f mousePos) {
    this->buttonState = BTN_IDLE;
    //hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;

        //TODO:: Trasforma in eventi con handleEvent
        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->locked) {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState) {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            this->text.setFillColor(this->textIdleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::White);
    }
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

void GUI::Button::handleEvent(sf::Event &event, const sf::Vector2f mousePos) {
    if (this->shape.getGlobalBounds().contains(mousePos) &&
        event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        this->locked = true;
        return;
    }

    this->locked = false;
}
