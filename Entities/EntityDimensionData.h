#ifndef SFML_ENTITYDIMENSIONDATA_H
#define SFML_ENTITYDIMENSIONDATA_H

#include <System/Vector2.hpp>


struct EntityDimensionData {
    EntityDimensionData(sf::Vector2f _position, sf::Rect<float> _size) : position(_position), size(_size) {};

    sf::Vector2f position;
    sf::Rect<float> size;

};

#endif //SFML_ENTITYDIMENSIONDATA_H



