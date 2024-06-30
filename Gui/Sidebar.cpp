#include <string>
#include "Sidebar.h"
#include "Utils.h"
#include "SwitchButton.h"
#include "PushButton.h"

GUI::Sidebar::Sidebar(sf::VideoMode &vm, sf::Font &font, std::vector<SidebarButton> &buttonsKeyLabel) : vm(vm),
                                                                                                        font(font),
                                                                                                        buttonsKeyLabel(
                                                                                                                buttonsKeyLabel) {
    this->initContainer();
    this->initButtons();
}

GUI::Sidebar::~Sidebar() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
}

void GUI::Sidebar::initContainer() {
    this->container.setPosition(static_cast<float>(vm.width) - GUI::Utils::p2px(4, vm), 0);
    this->container.setSize(sf::Vector2f(GUI::Utils::p2px(4, vm), GUI::Utils::p2py(100, vm)));
    this->container.setFillColor(sf::Color(50, 50, 50, 100));
    this->container.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->container.setOutlineThickness(1.f);
}

void GUI::Sidebar::update(float dt, sf::Vector2<int> mousePosition) {
    /*Updates all buttons in state and handles their functionality*/
    for (auto &button: this->buttons) {
        button.second->update(static_cast<sf::Vector2f>(mousePosition));
    }
}

void GUI::Sidebar::render(sf::RenderTarget &target) {
    target.draw(this->container);

    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void GUI::Sidebar::initButtons() {
    int index = 0;
    for (const auto &[key, label, isSwitch]: buttonsKeyLabel) {
        this->createButton(key, label, index, isSwitch);
        ++index;
    }
}

void GUI::Sidebar::createButton(const std::string &key, const std::string &label, int positionMultiplier,
                                bool isSwitch = false) {
    float x = vm.width - GUI::Utils::p2px(4, vm);
    float y = (GUI::Utils::p2px(4, vm) * positionMultiplier);
    float width = GUI::Utils::p2px(4, vm);
    float height = GUI::Utils::p2px(4, vm);

    if (isSwitch) {
        this->buttons[key] = new GUI::SwitchButton(x, y, width, height, &this->font, label,
                                                   GUI::Utils::charSize(vm),
                                                   CssColor::ClassicText(), CssColor::ClassicButton());
    } else {
        this->buttons[key] = new GUI::PushButton(x, y, width, height, &this->font, label,
                                                 GUI::Utils::charSize(vm),
                                                 CssColor::ClassicText(), CssColor::ClassicButton());
    }
}

sf::FloatRect GUI::Sidebar::getGlobalBounds() {
    return this->container.getGlobalBounds();
}

sf::Vector2f GUI::Sidebar::getSize() {
    return this->container.getSize();
}

bool GUI::Sidebar::isButtonClicked(std::string key) {
    return this->buttons[key]->isClicked();
}

void GUI::Sidebar::handleEvent(sf::Event &event, const float &dt, sf::Vector2<int> mousePosition) {
    for (auto &button: this->buttons) {
        button.second->handleEvent(event, static_cast<sf::Vector2f>(mousePosition));
    }
}

GUI::Button *GUI::Sidebar::getButton(std::string key) {
    return this->buttons[key];
}
