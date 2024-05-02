//
// Created by malte on 25/02/2024.
//

#ifndef SFML_GRAPHICSSETTINGS_H
#define SFML_GRAPHICSSETTINGS_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <string>

class GraphicsSettings {
public:
    //region Public Properties
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    unsigned frameRateLimit;
    bool verticalSync;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    //endregion

    //region Methods
    explicit GraphicsSettings(std::string &path);

    virtual ~GraphicsSettings();

    void save();

    void load();
    //endregion

private:
    std::string path;
};


#endif //SFML_GRAPHICSSETTINGS_H
