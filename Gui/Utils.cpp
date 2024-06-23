#include <cmath>
#include "Utils.h"

float GUI::Utils::p2px(const float percentage, const sf::VideoMode &vm) {
    return std::floor(vm.width * (percentage / 100.f));
}

float GUI::Utils::p2py(const float percentage, const sf::VideoMode &vm) {
    return std::floor(vm.height * (percentage / 100.f));
}

unsigned GUI::Utils::charSize(const sf::VideoMode &vm) {
    return (vm.width + vm.height) / 85;
}