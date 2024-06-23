#include "PlayerGUI.h"

GUI::PlayerGUI::PlayerGUI(Player *player) : player(player) {
    this->initFont();
    ProgressBarData data(sf::Vector2f(30.f, 20.f), this->player->getMaxHp(), this->player->getCurrentHp());
    this->hpBar = new GUI::HealthBar(data);
}

GUI::PlayerGUI::~PlayerGUI() {
    delete this->hpBar;
}

void GUI::PlayerGUI::render(sf::RenderTarget &target) {
    this->hpBar->render(target);
}

void GUI::PlayerGUI::update(const float &dt) {
    ProgressBarData data(sf::Vector2f(30.f, 20.f), this->player->getMaxHp(), this->player->getCurrentHp());
    this->hpBar->update(data);
}

void GUI::PlayerGUI::initFont() {
    this->font.loadFromFile("Fonts/Dosis-light.ttf");
}
