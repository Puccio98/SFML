#pragma once

#include <SFML/Graphics.hpp>
#include "../../Helper/Json/Serializable.h"

struct MapObjectData : Serializable {
    // deve diventare map object type
    TILE_TYPES type;
    int index_x;
    int index_y;
    int index_z;
    float gridSize;
    /**
    * Definisce le posizioni della texture nello sheet, quindi determina la texture da applicare
    */
    std::vector<sf::Vector2f> texturePositions;
    std::vector<sf::RectangleShape> sprites;

    json to_json() const override {
        json j;
        // Posizione tile nella mappa
        j["posizione"] = {{"x", index_x},
                          {"y", index_y},
                          {"z", index_z}};

        // Array di texture
        j["textures"] = nlohmann::json::array();
        for (const auto &pos: sprites) {
            j["textures"].push_back({{"x", pos.getTextureRect().left},
                                     {"y", pos.getTextureRect().top}});
        }
        return j;
    };


    // Deserialize from JSON
    void from_json(const json &j) override {
        // Parsing the position
        j.at("posizione").at("x").get_to(index_x);
        j.at("posizione").at("y").get_to(index_y);
        j.at("posizione").at("z").get_to(index_z);

        // Parsing the texture positions
        texturePositions.clear();
        for (const auto &textureJson: j.at("textures")) {
            sf::Vector2f pos;
            textureJson.at("x").get_to(pos.x);
            textureJson.at("y").get_to(pos.y);
            texturePositions.push_back(pos);
        }
    };
};