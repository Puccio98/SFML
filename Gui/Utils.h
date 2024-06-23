//
// Created by malte on 23/06/2024.
//

#ifndef SFML_UTILS_H
#define SFML_UTILS_H


#include <Window/VideoMode.hpp>

namespace GUI {
    class Utils {
    public:
        static float p2px(const float percentage, const sf::VideoMode &vm);

        static float p2py(const float percentage, const sf::VideoMode &vm);

        static unsigned int charSize(const sf::VideoMode &vm, const float multiplier = 1.f);
    };
}

#endif //SFML_UTILS_H