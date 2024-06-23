#include "HealthBar.h"

GUI::HealthBar::HealthBar(const ProgressBarData &progressBarData) {
    this->init(progressBarData);
}

void GUI::HealthBar::update(const ProgressBarData &progressBarData) {
    for (int i = 0; i < this->hpContainers.size(); i++) {
        updateContainer(i, progressBarData);
    }
}

void GUI::HealthBar::render(sf::RenderTarget &target) {
    for (auto container: this->hpContainers) {
        target.draw(container);
    }
}

void GUI::HealthBar::init(const ProgressBarData &progressBarData) {
    this->fullHeartTexturePath = "Resources/images/sprites/hud/half_full_heart.png";
    this->emptyHeartTexturePath = "Resources/images/sprites/hud/half_empty_heart.png";
    this->hpContainers = std::vector<sf::RectangleShape>(progressBarData.maxValue);
    this->width = 6.f;
    this->height = 9.f;

    if(!this->fullHeartTexture.loadFromFile(this->fullHeartTexturePath) ||
            !this->emptyHeartTexture.loadFromFile(this->emptyHeartTexturePath)
    ) {
        throw "ERROR::HEALTHBAR::FAILED_TO_LOAD_HEART_TEXTURES";
    }

    for (int i = 0; i < this->hpContainers.size(); i++) {
        initContainer(i, progressBarData);
    }

    this->update(progressBarData);
}

void GUI::HealthBar::initContainer(int containerIndex, const ProgressBarData &progressBarData) {
    bool isFullHeart = containerIndex < progressBarData.currentValue;
    bool isEven = containerIndex % 2;
    bool heartPattern = containerIndex / 2 % 2; // piccola modifica grafica per non fare tutti i cuori sullo stesso piano
    int scaleFactor = 2;

    float x_pos = progressBarData.position.x + (containerIndex * (this->width * scaleFactor));
    float y_pos = progressBarData.position.y + (heartPattern ? (this->height * scaleFactor / 2) : 0.f);

    sf::RectangleShape rectangle(sf::Vector2f(this->width, this->height));

    rectangle.setTexture(isFullHeart? &fullHeartTexture : &emptyHeartTexture);
    sf::IntRect textureRect = rectangle.getTextureRect();

    rectangle.setPosition(x_pos, y_pos);
    rectangle.setScale(scaleFactor, scaleFactor);

    if (isEven) {
        // Flip the texture horizontally
        textureRect.left = this->width;
        textureRect.width = -textureRect.width; // Set width to negative to flip
    }

    rectangle.setTextureRect(textureRect);
    this->hpContainers[containerIndex] = rectangle;
}

void GUI::HealthBar::updateContainer(int containerIndex, const ProgressBarData &progressBarData) {

}

GUI::HealthBar::~HealthBar()  = default;
