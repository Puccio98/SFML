#include <stack>
#include <System/Vector2.hpp>
#include <vector>

struct ProgressBarData {
    sf::Vector2f position;
    float maxValue;
    float currentValue;

    ProgressBarData(const sf::Vector2f &position, float maxValue, float currentValue) : position(position),
                                                                                        maxValue(maxValue),
                                                                                        currentValue(currentValue) {}
};

