#pragma once

#include "../MapObjectData.h"

struct EnemySpawnerData : MapObjectData {
    ENEMY_TYPES enemy_type;

    explicit EnemySpawnerData(ENEMY_TYPES enemyType) : enemy_type(enemyType) {}

    json to_json() const override {
        json j = MapObjectData::to_json();

        if (this->type == MAP_OBJECTS::SPAWNER) {
            j["enemy_type"] = this->enemy_type;
        }
        return j;
    };


    // Deserialize from JSON
    void from_json(const json &j) override {
        MapObjectData::from_json(j);

        auto it = j.find("enemy_type");
        if (it != j.end()) {
            it->get_to(enemy_type);
        }
    };
};