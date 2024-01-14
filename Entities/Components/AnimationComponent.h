#ifndef SFML_ANIMATIONCOMPONENT_H
#define SFML_ANIMATIONCOMPONENT_H

#include "Animation.h"

class AnimationComponent {
private:

    sf::Sprite &sprite;
    sf::Texture &texture_sheet;
    std::map<std::string, Animation *> animations;
    Animation *lastAnimation;

public:
    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);

    virtual ~AnimationComponent();

    void addAnimation(std::string key, float animation_timer,
                      int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width,
                      int height);

    void play(const std::string &key, const float &dt, const float &mod_percent = 1.f, bool priority = false);

    void updateAnimation(std::string animation);
};


#endif //SFML_ANIMATIONCOMPONENT_H
