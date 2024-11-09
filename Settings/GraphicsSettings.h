#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <string>

class GraphicsSettings {
public:
    //region Public Properties
    std::string title;
    sf::VideoMode defaultResolution;
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