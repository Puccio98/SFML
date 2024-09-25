#include "PlayerGUI.h"
#include "Utils.h"

GUI::PlayerGUI::PlayerGUI(Player *player, sf::VideoMode &resolution) : player(player), resolution(resolution) {
    this->initFont();
    ProgressBarData data(sf::Vector2f(GUI::Utils::p2px(1, resolution), GUI::Utils::p2py(1.5, resolution)),
                         this->player->getMaxHp(), this->player->getCurrentHp());
    this->hpBar = new GUI::HealthBar(data);
}

GUI::PlayerGUI::~PlayerGUI() {
    delete this->hpBar;
}

void GUI::PlayerGUI::render(sf::RenderTarget &target) {
    this->hpBar->render(target);
}

void GUI::PlayerGUI::update(const float &dt) {
    ProgressBarData data(sf::Vector2f(GUI::Utils::p2px(1, resolution), GUI::Utils::p2py(1.5, resolution)),
                         this->player->getMaxHp(), this->player->getCurrentHp());
    this->hpBar->update(data);
}

void GUI::PlayerGUI::initFont() {
    this->font.loadFromFile("Fonts/Dosis-light.ttf");
}
