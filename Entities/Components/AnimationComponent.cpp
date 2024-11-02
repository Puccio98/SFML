#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) : sprite(sprite),
                                                                                         texture_sheet(texture_sheet) {}

AnimationComponent::~AnimationComponent() {
    for (auto &i: this->animations) {
        delete i.second;
    }
}

void AnimationComponent::play(const std::string &key, const float &dt, const float &mod_percent) {
    // if same animation or first time
    if (this->currentAnimation.first == key || this->currentAnimation.second == nullptr) {
        this->currentAnimation = std::pair(key, this->animations[key]);
        return this->animations[key]->play(dt, (mod_percent));
    }

    // if different animation, handle animation priority (animazione cambiata)
    if (!this->currentAnimation.second->canBeInterrupted && !this->currentAnimation.second->isAnimationAboutToRestart(
            dt)) {
        return this->animations[this->currentAnimation.first]->play(dt, (mod_percent));
    }

    // generic case
    this->animations[this->currentAnimation.first]->reset();
    this->currentAnimation = std::pair(key, this->animations[key]);
    return this->animations[key]->play(dt, (mod_percent));
}

void AnimationComponent::addAnimation(const std::string &key,
                                      float animation_timer, int start_frame_x, int start_frame_y, int end_frame_x,
                                      int end_frame_y, int width, int height, bool canBeInterrupted) {
    this->animations[key] = new Animation(this->sprite, this->texture_sheet, animation_timer, start_frame_x,
                                          start_frame_y,
                                          end_frame_x, end_frame_y, width, height, canBeInterrupted);
}

std::string AnimationComponent::getCurrentAnimationKey() const {
    return this->currentAnimation.first;
}

const std::pair<std::string, Animation *> &AnimationComponent::getCurrentAnimation() const {
    return currentAnimation;
}
