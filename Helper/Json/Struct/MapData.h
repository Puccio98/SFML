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

    // Tiles
    std::vector<std::vector<std::vector<Tile *>>> tiles;

    // non serializza
    sf::Vector2f maxSizeWorld;
    sf::Texture tileTextureSheet;
    sf::Font &font;
    bool hud;

    MapData(sf::Font &font, bool hud) : font(font), hud(hud) {
    }

    // Functions
    json to_json() const override {
        json j;

        j["maxSizeGrid"] = {{"x", this->maxSizeGrid.x},
                            {"y", this->maxSizeGrid.y}};
        j["gridSizeU"] = this->gridSizeU;
        j["maxLayerIndex"] = this->maxLayerIndex;
        j["texturePath"] = this->texturePath;

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
        // Parse base data
        j.at("maxSizeGrid").at("x").get_to(this->maxSizeGrid.x);
        j.at("maxSizeGrid").at("y").get_to(this->maxSizeGrid.y);
        j.at("gridSizeU").get_to(this->gridSizeU);
        j.at("maxLayerIndex").get_to(this->maxLayerIndex);
        j.at("texturePath").get_to(this->texturePath);

        this->gridSizeF = static_cast<float>(this->gridSizeU);
        this->maxSizeWorld.x = static_cast<float>(this->maxSizeGrid.x * this->gridSizeU);
        this->maxSizeWorld.y = static_cast<float>(this->maxSizeGrid.y * this->gridSizeU);
        // Clear existing tiles to avoid memory leaks
        for (auto &row: this->tiles) {
            for (auto &column: row) {
                for (auto &tile: column) {
                    delete tile;
                }
            }
        }
        this->tiles.clear();

        // Initialize tiles based on the grid size
        this->tiles.resize(this->maxSizeGrid.x);
        for (auto &row: this->tiles) {
            row.resize(this->maxSizeGrid.y);
        }

        if (!this->tileTextureSheet.loadFromFile(this->texturePath)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME:" << this->texturePath << "\n";
        }

        // Populate tiles from JSON
        const auto &json_tiles = j.at("tiles");
        for (const auto &tile_json: json_tiles) {
            TileData tileData;
            tileData.from_json(tile_json);

            int x = tileData.index_x;
            int y = tileData.index_y;
            int z = tileData.index_z;
            tileData.gridSize = this->gridSizeF;

            // Ensure the vector is large enough
            if (x >= this->tiles.size() || y >= this->tiles[x].size()) {
                continue; // Handle out-of-bounds safely
            }

            if (z >= this->tiles[x][y].size()) {
                this->tiles[x][y].resize(z + 1);
            }

            this->tiles[x][y][z] = GetTile(tileData);
        }
    };

    virtual ~MapData() {
        for (auto &row: this->tiles) {
            for (auto &column: row) {
                for (auto &tile: column) {
                    delete tile;
                }
            }
        }
    }

private:
    Tile *GetTile(const TileData &tileData) {
        switch (tileData.type) {
            case TILE_TYPES::DEFAULT:
                return new Tile(tileData,
                                this->tileTextureSheet,
                                this->font,
                                this->hud);
            case TILE_TYPES::SPAWNER:
                break;
            case TILE_TYPES::WARP:
                break;
        }
        return nullptr;
    }
};