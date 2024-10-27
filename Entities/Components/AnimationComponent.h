#ifndef SFML_ANIMATIONCOMPONENT_H
#define SFML_ANIMATIONCOMPONENT_H

#include "Animation.h"

class AnimationComponent {
private:

    sf::Sprite &sprite;
    sf::Texture &texture_sheet;
    std::map<std::string, Animation *> animations;
    std::pair<std::string, Animation *> currentAnimation;

public:
    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);

    virtual ~AnimationComponent();

    void addAnimation(const std::string &key, float animation_timer,
                      int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width,
                      int height, bool canBeInterrupted = true);

    void play(const std::string &key, const float &dt, const float &mod_percent = 1.f);

    std::string getCurrentAnimationKey() const;

    const std::pair<std::string, Animation *> &getCurrentAnimation() const;

    void setCurrentAnimation(const std::pair<std::string, Animation *> &currentAnimation);

    void reset();
};


#endif //SFML_ANIMATIONCOMPONENT_H
