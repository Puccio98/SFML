#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) : sprite(sprite),
                                                                                         texture_sheet(texture_sheet),
                                                                                         lastAnimation(nullptr) {}

AnimationComponent::~AnimationComponent() {
    for (auto &i: this->animations) {
        delete i.second;
    }
}

void AnimationComponent::play(const std::string &key, const float &dt, const float &mod_percent, const bool priority) {
    if (this->lastAnimation != this->animations[key]) {
        if (this->lastAnimation != nullptr)
            this->lastAnimation->reset();
        this->lastAnimation = this->animations[key];
    }

    this->animations[key]->play(dt, (mod_percent));
}

void AnimationComponent::updateAnimation(std::string animation) {

}

void AnimationComponent::addAnimation(const std::string key,
                                      float animation_timer, int start_frame_x, int start_frame_y, int frames_x,
                                      int frames_y, int width, int height) {
    this->animations[key] = new Animation(this->sprite, this->texture_sheet, animation_timer, start_frame_x,
                                          start_frame_y,
                                          frames_x, frames_y, width, height);
}



