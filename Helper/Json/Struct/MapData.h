#include <System/Vector2.hpp>
#include <string>
#include <vector>
#include "../../../Tile/Tile.h"

#ifndef SFML_MAPDATA_H
#define SFML_MAPDATA_H

#endif //SFML_MAPDATA_H

struct MapData : Serializable {
    // Base Data
    unsigned gridSizeU;
    float gridSizeF;
    unsigned maxLayerIndex;
    sf::Vector2u maxSizeGrid;
    std::string texturePath;

    //Tiles
    std::vector<std::vector<std::vector<Tile *>>> tiles;

    //Functions
    json to_json() const override {
        json j;

        j["maxSizeGrid"] = {{"x", this->maxSizeGrid.x},
                            {"y", this->maxSizeGrid.y}};
        j["gridSizeU"] = {this->gridSizeU};
        j["maxLayerIndex"] = {this->maxLayerIndex};
        j["texturePath"] = {this->texturePath};

        j["tiles"] = nlohmann::json::array();

        for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
            for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
                for (size_t z = 0; z < this->tiles[x][y].size(); z++) {
                    j["tiles"].push_back(this->tiles[x][y][z]->getTiledata().to_json());
                }
            }
        }
        return j;
    };


    void from_json(const json &j) override {
//        j.at("name").get_to(p.name);
//        j.at("age").get_to(p.age);
//        j.at("city").get_to(p.city);
    };


    virtual ~MapData() {
        for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
            for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
                while (this->map[x][y].size() != 0) {
                    delete this->map[x][y].at(this->map[x][y].size() - 1);
                    this->map[x][y].pop_back();
                }
                this->map[x][y].clear();
            }
            this->map[x].clear();
        }

        this->map.clear();
    }
};