#ifndef SFML_SERIALIZABLE_H
#define SFML_SERIALIZABLE_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

// Include nlohmann::json namespace for convenience
using json = nlohmann::json;

// Base Interface class with pure virtual methods
class Serializable {
public:
    virtual ~Serializable() = default;

    // Pure virtual methods
    /**
     * Crea un json a partire dai valori della struct
     * @param j
     */
    virtual json to_json() const = 0;

    /**
     * Inizializza la struct con i valori del json
     * @param j
     */
    virtual void from_json(const json &j) = 0;
};

#endif //SFML_SERIALIZABLE_H
