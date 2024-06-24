#include "Utils.h"

float GUI::Utils::p2px(const float percentage, const sf::VideoMode &vm) {
    return std::floor(vm.width * (percentage / 100.f));
}

float GUI::Utils::p2py(const float percentage, const sf::VideoMode &vm) {
    return std::floor(vm.height * (percentage / 100.f));
}

unsigned GUI::Utils::charSize(const sf::VideoMode &vm, const float multiplier) {
    return ((vm.width + vm.height) / 85 * multiplier);
}

void GUI::Utils::renderByView(sf::RenderTarget *target, sf::View newView,
                              const std::function<void(sf::RenderTarget *)> &customFunction) {
    auto const &oldView = target->getView();
    target->setView(newView);
    customFunction(target);
    target->setView(oldView);
}