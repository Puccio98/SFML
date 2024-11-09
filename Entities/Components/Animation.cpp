#include "Animation.h"

Animation::~Animation() = default;

void Animation::play(const float &dt, float mod_percent) {
    // Ensure mod_percent is within acceptable range
    mod_percent = std::abs(mod_percent);
    if (mod_percent < 0.5f) mod_percent = 0.5f;

    // Increment timers
    this->frameTimer += mod_percent * this->magicNumber * dt;
    this->animationTimer += mod_percent * this->magicNumber * dt;

    // Handle entire animation duration
    if (this->animationTimer >= this->animationDuration) {
        this->animationTimer = 0.f;
    }

    // Handle single frame duration
    if (this->frameTimer >= this->frameDuration) {
        // Reset frameTimer
        this->frameTimer -= this->frameDuration;

        // Update frame position
        if (this->currentRect != this->endRect) {
            this->currentRect.left += this->width;
        } else {
            // Reset to start position
            this->currentRect.left = this->startRect.left;
        }

        // Update sprite texture
        this->sprite.setTextureRect(this->currentRect);
    }
}


void Animation::reset() {
    this->frameTimer = 0.f;
    this->animationTimer = 0.f;
    this->currentRect = this->startRect;
}

Animation::Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float animation_duration,
                     int start_frame_x, int start_frame_y, int end_frames_x, int end_frames_y,
                     int width, int height, bool canBeInterrupted)
        : sprite(sprite),
          textureSheet(texture_sheet),
          animationLength(end_frames_x - start_frame_x + 1),
          frameDuration(animation_duration / (end_frames_x - start_frame_x + 1)),
          animationDuration(animation_duration),
          width(width),
          height(height),
          frameTimer(0.f),
          animationTimer(0.f),
          startRect(start_frame_x * width, start_frame_y * height, width, height),
          currentRect(startRect),
          endRect(end_frames_x * width, end_frames_y * height, width, height),
          canBeInterrupted(canBeInterrupted) {
    this->sprite.setTexture(this->textureSheet, true);
    this->sprite.setTextureRect(this->startRect);
}

bool Animation::isAnimationAboutToRestart(const float &dt, float mod_percent) const {
    float at = this->animationTimer + mod_percent * this->magicNumber * dt;
    return at >= this->animationDuration;
}

float Animation::getAnimationProgress() const {
    return (this->currentRect.left / this->width) / (this->animationLength);
}

