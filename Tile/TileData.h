#include <vector>
#include <System/Vector2.hpp>
#include"../enums/tile_types.cpp"
#include "../Helper/Json/Serializable.h"

struct TileData : Serializable {
    int index_x;
    int index_y;
    int index_z;
    float gridSize;
    /**
     * Definisce le posizioni della texture nello sheet, quindi determina la texture da applicare
     */
    std::vector<sf::Vector2f> texturePositions;
    std::vector<sf::RectangleShape> sprites;
    std::vector<TILE_BEHAVIOURS> behaviours;

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

        // Behaviours
        j["behaviours"] = nlohmann::json::array();
        for (const auto &behaviour: behaviours) {
            j["behaviours"].push_back(behaviour);
        }

        // Tile type
        j["type"] = {0};
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

        // Parsing the behaviours
        behaviours.clear();
        for (const auto &behaviourJson: j.at("behaviours")) {
            TILE_BEHAVIOURS behaviour;
            behaviourJson.get_to(behaviour);
            behaviours.push_back(behaviour);
        }
    };
};