#include "CoffeMachine.h"


CoffeMachine::CoffeMachine(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud)
        : Tile(std::move(tileData), texture, font, hud) {
    this->initTextures();
    this->layerText.setString(this->layerText.getString() + "\n" + "Save");
    this->layerText.setFillColor(sf::Color(200, 200, 30));
}

CoffeMachine::CoffeMachine(TileData tileData, sf::Texture &texture, sf::Font &font)
        : CoffeMachine(std::move(tileData), texture, font, false) {
}

void CoffeMachine::initTextures() {
    std::string coffe_machine_sheet = "Resources/images/sprites/element/coffe_machine.png";

    // Carica la texture
    if (!this->textures["COFFE_MACHINE_SHEET"].loadFromFile(coffe_machine_sheet)) {
        throw "ERROR::COFFE_MACHINE::COULD_NOT_COFFE_MACHINE_TEXTURE";
    }
}