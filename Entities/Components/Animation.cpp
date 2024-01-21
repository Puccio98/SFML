#include "Animation.h"

Animation::~Animation() = default;

void Animation::play(const float &dt, float mod_percent) {
    mod_percent = std::abs(mod_percent);
    if (mod_percent < 0.5f) mod_percent = 0.3f;
    this->timer += (mod_percent) * 30.f * dt;
    if (this->timer >= this->animationTimer) {
        //reset timer
        this->timer = 0.f;

        //Animate
        if (this->currentRect != this->endRect) {
            this->currentRect.left += this->width;
        } else //Reset
        {
            this->currentRect.left = this->startRect.left;
        }
        this->sprite.setTextureRect(this->currentRect);
    }
}

void Animation::reset() {
    this->timer = animationTimer;
    this->currentRect = this->startRect;
}

Animation::Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float animation_timer,
                     int start_frame_x, int start_frame_y, int frames_x, int frames_y,
                     int width, int height, bool canBeInterrupted) : sprite(sprite), textureSheet(texture_sheet) {
    this->width = width;
    this->height = height;
    this->animationTimer = animation_timer;

    this->timer = 0.f;
    this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
    this->currentRect = this->startRect;
    this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

    this->sprite.setTexture(this->textureSheet, true);
    this->sprite.setTextureRect(this->startRect);

    this->canBeInterrupted = canBeInterrupted;
}

bool Animation::isFinished() const {
    return this->currentRect == this->endRect;
}

