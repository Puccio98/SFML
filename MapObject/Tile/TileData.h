#pragma once

#include <vector>
#include"../../enums/behaviour_types.cpp"
#include "../../enums/tile_types.cpp"
#include "../../enums/enemy_types.cpp"
#include "MapObjectData.h"

struct TileData : public MapObjectData {
    ENEMY_TYPES enemy_type;
    std::vector<TILE_BEHAVIOURS> behaviours;

    json to_json() const override {
        json j = MapObjectData::to_json();

        // Behaviours
        j["behaviours"] = nlohmann::json::array();
        for (const auto &behaviour: behaviours) {
            j["behaviours"].push_back(behaviour);
        }

        // Tile type
        j["type"] = this->type;             // Tile type
        if (this->type == TILE_TYPES::SPAWNER) {
            j["enemy_type"] = this->enemy_type;
        }
        return j;
    };


    // Deserialize from JSON
    void from_json(const json &j) override {
        MapObjectData::from_json(j);

        // Parsing the behaviours
        behaviours.clear();
        for (const auto &behaviourJson: j.at("behaviours")) {
            TILE_BEHAVIOURS behaviour;
            behaviourJson.get_to(behaviour);
            behaviours.push_back(behaviour);
        }

        j.at("type").get_to(type);
        auto it = j.find("enemy_type");
        if (it != j.end()) {
            it->get_to(enemy_type);
        }
    };
};