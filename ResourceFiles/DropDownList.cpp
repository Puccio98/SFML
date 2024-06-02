#include "DropDownList.h"
#include "PushButton.h"

GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font &font,
                                std::vector<std::string> &options,
                                unsigned default_index) : font(font),
                                                          showList(false) {
    this->selectedElementId = default_index;
    unsigned nrOfElements = options.size();


    CssColor textColor = CssColor(sf::Color(120, 50, 80, 200),
                                  sf::Color(150, 50, 80, 250),
                                  sf::Color(90, 40, 60, 50));

    CssColor buttonColor = CssColor(sf::Color(120, 50, 80, 0),
                                    sf::Color(150, 50, 80, 0),
                                    sf::Color(90, 40, 60, 0));

    this->activeElement = new GUI::PushButton(x, y, width, height, &this->font, options[default_index], 12,
                                              textColor, buttonColor);

    for (size_t i = 0; i < nrOfElements; i++) {
        this->buttons.push_back(
                new GUI::PushButton(x, y + (height * ((float) i + 1)), width, height, &this->font, options[i], 12,
                                    textColor, buttonColor, i));
    }
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

            if (button->isPressed()) {
                this->selectedElementId = button->getId();
                this->activeElement->setText(button->getText());
                this->showList = false;
            }
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
}

unsigned short GUI::DropDownList::getSelectedElementId() const {
    return this->selectedElementId;
};
