#pragma once

#include <vector>
#include"../../enums/behaviour_types.cpp"
#include "../../enums/enemy_types.cpp"
#include "../MapObjectData.h"

struct TileData : public MapObjectData {
    std::vector<TILE_BEHAVIOURS> behaviours;

    explicit TileData() : MapObjectData(MAP_OBJECTS::TILE) {
        this->behaviours = std::vector<TILE_BEHAVIOURS>();
    }

    json to_json() const override {
        json j = MapObjectData::to_json();

        // Behaviours
        j["behaviours"] = nlohmann::json::array();
        for (const auto &behaviour: behaviours) {
            j["behaviours"].push_back(behaviour);
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
    };
};