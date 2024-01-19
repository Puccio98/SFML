#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) : sprite(sprite),
                                                                                         texture_sheet(texture_sheet),
                                                                                         lastAnimation(nullptr) {}

AnimationComponent::~AnimationComponent() {
    for (auto &i: this->animations) {
        delete i.second;
    }
}

void AnimationComponent::play(const std::string &key, const float &dt, const float &mod_percent) {
    // same animation or first time
    if (this->lastAnimation == this->animations[key] || this->lastAnimation == nullptr) {
        this->lastAnimation = this->animations[key];
        return this->animations[key]->play(dt, (mod_percent));
    }

    // handle animation priority (animazione cambiata)
    if (!this->lastAnimation->canBeInterrupted && !this->lastAnimation->isFinished()) {
        return this->lastAnimation->play(dt, (mod_percent));
    }

    // generic case
    this->lastAnimation->reset();
    this->lastAnimation = this->animations[key];
    return this->animations[key]->play(dt, (mod_percent));
}

void AnimationComponent::addAnimation(const std::string &key,
                                      float animation_timer, int start_frame_x, int start_frame_y, int frames_x,
                                      int frames_y, int width, int height, bool canBeInterrupted) {
    this->animations[key] = new Animation(this->sprite, this->texture_sheet, animation_timer, start_frame_x,
                                          start_frame_y,
                                          frames_x, frames_y, width, height, canBeInterrupted);
}



