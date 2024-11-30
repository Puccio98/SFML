#pragma once

#include "../../../MapObject/EnemySpawner/EnemySpawner.h"
#include "../../../MapObject/EnemySpawner/EnemySpawnerData.h"

struct MapData : Serializable {
    // Base Data
    unsigned gridSizeU;
    float gridSizeF;
    unsigned maxLayerIndex;
    sf::Vector2u maxSizeGrid;
    std::string texturePath;

    // Tiles
    std::vector<std::vector<std::vector<Tile *>>> tiles;
    // Mappa degli oggetti
    std::map<int, std::map<int, std::map<int, MapObject *>>> objects;

    static MapObject *findMapObject(
            const std::map<int, std::map<int, std::map<int, MapObject *>>> &objects,
            int i, int j, int layerIndex) {
        auto iIt = objects.find(i);
        if (iIt != objects.end()) {
            auto jIt = iIt->second.find(j);
            if (jIt != iIt->second.end()) {
                auto layerIt = jIt->second.find(layerIndex);
                if (layerIt != jIt->second.end()) {
                    return layerIt->second; // Return the MapObject* if found
                }
            }
        }
        return nullptr; // Return nullptr if not found
    }


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
        j["objects"] = nlohmann::json::array();

        for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
            for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
                for (size_t z = 0; z < this->tiles[x][y].size(); z++) {
                    // Push tile data to JSON
                    j["tiles"].push_back(this->tiles[x][y][z]->getTiledata()->to_json());

                    // Check if the object exists in the map at (x, y, z)
                    auto itX = this->objects.find(x);
                    if (itX != this->objects.end()) {
                        auto itY = itX->second.find(y);
                        if (itY != itX->second.end()) {
                            auto itZ = itY->second.find(z);
                            if (itZ != itY->second.end() && itZ->second != nullptr) {
                                auto pippo = itZ->second;
                                j["objects"].push_back(pippo->getData()->to_json());
                            }
                        }
                    }
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

        this->load_tiles_from_json(j);
        this->load_objects_from_json(j);
    }

    void load_tiles_from_json(const json &j) {// Clear existing tiles to avoid memory leaks
        for (auto &row: tiles) {
            for (auto &column: row) {
                for (auto &tile: column) {
                    delete tile;
                }
            }
        }
        tiles.clear();


        // Initialize tiles based on the grid size
        tiles.resize(maxSizeGrid.x);
        for (auto &row: tiles) {
            row.resize(maxSizeGrid.y);
        }

        if (!tileTextureSheet.loadFromFile(texturePath)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME:" << texturePath << "\n";
        }

        // Populate tiles from JSON
        const auto &json_tiles = j.at("tiles");
        for (const auto &tile_json: json_tiles) {
            TileData tileData;
            tileData.from_json(tile_json);

            int x = tileData.index_x;
            int y = tileData.index_y;
            int z = tileData.index_z;
            tileData.gridSize = gridSizeF;

            // Ensure the vector is large enough
            if (x >= tiles.size() || y >= tiles[x].size()) {
                continue; // Handle out-of-bounds safely
            }

            if (z >= tiles[x][y].size()) {
                tiles[x][y].resize(z + 1);
            }

            tiles[x][y][z] = GetTile(tileData);
        }
    };


    void load_objects_from_json(const json &j) {
        for (auto &[key1, innerMap1]: objects) {
            for (auto &[key2, innerMap2]: innerMap1) {
                for (auto &[key3, objPtr]: innerMap2) {
                    delete objPtr;
                }
                innerMap2.clear();
            }
            innerMap1.clear();
        }
        objects.clear();

        // Populate objects from JSON
        const auto &json_objects = j.at("objects");
        for (const auto &object_json: json_objects) {
            MAP_OBJECTS type = object_json.at("type");
            // check is not null

            MapObjectData *mpData = getMapObjectData(type);
            mpData->from_json(object_json);
            int x = mpData->index_x;
            int y = mpData->index_y;
            int z = mpData->index_z;
            mpData->gridSize = gridSizeF;

            this->objects[x][y][z] = GetObject(mpData);
        }
    }

    virtual ~MapData() {
        for (auto &row: this->tiles) {
            for (auto &column: row) {
                for (auto &tile: column) {
                    delete tile;
                }
            }
        }
    }

    void addTile(const TileData tileData) {
        this->tiles[tileData.index_x][tileData.index_y].push_back(this->GetTile(tileData));
    }


    void addObject(MapObjectData *data) {
        // Access or create the nested map for index_x
        auto &level_x = this->objects[data->index_x];

        // Access or create the nested map for index_y
        auto &level_y = level_x[data->index_y];

        // Replace the MapObject pointer at index_z
        level_y[data->index_z] = this->GetObject(data);
    }


private:
    Tile *GetTile(const TileData &tileData) {
        return new Tile(tileData,
                        this->tileTextureSheet,
                        this->font,
                        this->hud);
    }


    MapObject *GetObject(MapObjectData *pObject) {
        switch (pObject->type) {
            case MAP_OBJECTS::SPAWNER: {
                auto ptr = dynamic_cast<EnemySpawnerData *>(pObject);
                return new EnemySpawner(ptr, this->tileTextureSheet, this->font,
                                        this->hud,
                                        EntityDimensionData(sf::Vector2f(pObject->gridSize * pObject->index_x,
                                                                         pObject->gridSize * pObject->index_y),
                                                            sf::Vector2(pObject->gridSize, pObject->gridSize)
                                        ),
                                        ptr->enemy_type, 0, 0, 0);
            }
            case MAP_OBJECTS::ELEMENT:
                break;
            default:
                throw ("ERROR::MAPDATA COULD NOT DETERMINE OBJECT TYPE");
        };
        return nullptr;
    }

    MapObjectData *getMapObjectData(MAP_OBJECTS objects) {
        switch (objects) {
            case MAP_OBJECTS::SPAWNER: {
                return new EnemySpawnerData();
            }
            case MAP_OBJECTS::ELEMENT:
                break;
            default:
                throw ("ERROR::MAPDATA COULD NOT DETERMINE OBJECT TYPE");
        };
        return nullptr;
    }
};