#ifndef SFML_COFFEMACHINE_H
#define SFML_COFFEMACHINE_H


#include "Tile.h"

class CoffeMachine : public Tile {
private:
    std::map<std::string, sf::Texture> textures;
public:
    CoffeMachine(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud);

    CoffeMachine(TileData tileData, sf::Texture &texture, sf::Font &font);

    void initTextures();
};


#endif //SFML_COFFEMACHINE_H
