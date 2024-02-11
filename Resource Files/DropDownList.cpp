#include "DropDownList.h"

GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font &font,
                                std::vector<std::string> &options,
                                unsigned default_index) : font(font),
                                                          showList(false) {
    unsigned nrOfElements = options.size();
    std::cout << "number of elements: " << nrOfElements;

    for (size_t i = 0; i < nrOfElements; i++) {
        this->buttons.push_back(new GUI::Button(x, y + (height * (float) i), width, height, &this->font, options[i], 12,
                                                sf::Color(120, 50, 80, 200),
                                                sf::Color(150, 50, 80, 250),
                                                sf::Color(90, 40, 60, 50),
                                                sf::Color(120, 50, 80, 0),
                                                sf::Color(150, 50, 80, 0),
                                                sf::Color(90, 40, 60, 0)));
    }

    this->activeElement = new Button(*this->buttons[default_index]);
}

void GUI::DropDownList::render(sf::RenderTarget &target) {
    if (this->showList) {
        for (auto &button: this->buttons) {
            button->render(target);
        }
    }
    this->activeElement->render(target);
}

void GUI::DropDownList::update(const sf::Vector2f &mousePos) {
    this->activeElement->update(mousePos);

    if (this->showList) {
        for (auto &button: this->buttons) {
            button->update(mousePos);
        }
    }
}

GUI::DropDownList::~DropDownList() {
    delete this->activeElement;
    for (auto &i: this->buttons)
        delete i;
}

void GUI::DropDownList::handleEvent(sf::Event &event, const sf::Vector2f mousePos) {
    if (this->showList) {
        for (auto &button: this->buttons) {
            button->handleEvent(event, mousePos);
        }
    }
    this->activeElement->handleEvent(event, mousePos);
    if (this->activeElement->isPressed()) {
        this->showList = !this->showList;
    }
};
