#pragma once

#include <System/Vector2.hpp>


struct EntityDimensionData {
    EntityDimensionData(sf::Vector2f _position, sf::Vector2f _size) : position(_position), size(_size) {};

    sf::Vector2f position;
    sf::Vector2f size;

};