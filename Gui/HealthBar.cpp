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

    if(!this->fullHeartTexture.loadFromFile(this->fullHeartTexturePath) ||
            !this->emptyHeartTexture.loadFromFile(this->emptyHeartTexturePath)
    ) {
        throw "ERROR::HEALTHBAR::FAILED_TO_LOAD_HEART_TEXTURES";
    }

    this->update(progressBarData);
}

void GUI::HealthBar::updateContainer(int containerIndex, const ProgressBarData &progressBarData) {
    bool isFullHeart = containerIndex < progressBarData.currentValue;
    bool isEven = containerIndex % 2;
    bool heart_y_pattern = containerIndex / 2 % 2; // piccola modifica grafica per non fare tutti i cuori sullo stesso piano
    int scale_factor = 2;

    float x_pos = progressBarData.position.x + (containerIndex * (this->width * scale_factor));
    float y_pos = progressBarData.position.y + (heart_y_pattern ? (this->height * scale_factor / 2) : 0.f);

    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    sf::IntRect textureRect = rectangle.getTextureRect();

    rectangle.setTexture(isFullHeart? &fullHeartTexture : &emptyHeartTexture);
    rectangle.setPosition(x_pos, y_pos);
    rectangle.setScale(2.f, 2.f);

    if (isEven) {
        // Flip the texture horizontally
        textureRect.left = 6.f;
        textureRect.width = -textureRect.width; // Set width to negative to flip
    }

    rectangle.setTextureRect(textureRect);
    this->hpContainers[containerIndex] = rectangle;
}

GUI::HealthBar::~HealthBar()  = default;
