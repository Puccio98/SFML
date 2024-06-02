#include "PushButton.h"

GUI::PushButton::PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                            unsigned int characterSize, const sf::Color &textIdleColor, const sf::Color &textHoverColor,
                            const sf::Color &textActiveColor, const sf::Color &idleColor, const sf::Color &hoverColor,
                            const sf::Color &activeColor, unsigned short id) : Button(x, y, width, height,
                                                                                      font, text,
                                                                                      characterSize,
                                                                                      textIdleColor,
                                                                                      textHoverColor,
                                                                                      textActiveColor,
                                                                                      idleColor,
                                                                                      hoverColor,
                                                                                      activeColor, id),
                                                                               locked(false) {}

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


void GUI::PushButton::handleEvent(sf::Event &event, sf::Vector2f mousePos) {
    this->locked = this->shape.getGlobalBounds().contains(mousePos) &&
                   event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}

void GUI::PushButton::reset() {
    this->locked = false;
}

GUI::PushButton::~PushButton() {

}
