#include "ProgressBar.h"

GUI::ProgressBar::ProgressBar(const sf::Font &font, const ProgressBarData &progressBarData) : font(font) {
    this->init(progressBarData);
}

GUI::ProgressBar::~ProgressBar() = default;

void GUI::ProgressBar::init(const ProgressBarData &progressBarData) {
    this->progressBarBack.setSize(sf::Vector2f(this->width, this->height));
    this->progressBarBack.setFillColor(sf::Color(50, 50, 50, 200));

    this->update(progressBarData);
    this->progressBarFilled.setFillColor(sf::Color(0, 255, 0, 255));
}

void GUI::ProgressBar::update(const ProgressBarData &progressBarData) {
    float progress = calculateProgress(progressBarData.maxValue, progressBarData.currentValue);

    this->progressBarFilled.setPosition(progressBarData.position);
    this->progressBarBack.setPosition(progressBarData.position);
    this->progressBarFilled.setSize(sf::Vector2f(progress, this->height));
}

void GUI::ProgressBar::render(sf::RenderTarget &target) {
    target.draw(this->progressBarBack);
    target.draw(this->progressBarFilled);
}

float GUI::ProgressBar::calculateProgress(float maxValue, float currentValue) const {
    float progress = (currentValue / maxValue) * this->width;

    if (progress < 0) {
        return 0;
    }
    if (progress > this->width) {
        return this->width;
    }

    return progress;
}
