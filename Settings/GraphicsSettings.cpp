#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings(std::string &path) {
    this->path = path;
    this->title = "Uninitialized title";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->frameRateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::load() {
    std::ifstream ifs(this->path);

    if (ifs.is_open()) {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullscreen;
        ifs >> this->frameRateLimit;
        ifs >> this->verticalSync;
        ifs >> this->contextSettings.antialiasingLevel;
    }

    ifs.close();
}

void GraphicsSettings::save() {
    std::ofstream ofs(this->path);

    if (ofs.is_open()) {
        ofs << this->title << "\n";
        ofs << this->resolution.width << " " << this->resolution.height << "\n";
        ofs << this->fullscreen << "\n";
        ofs << this->frameRateLimit << "\n";
        ofs << this->verticalSync << "\n";
        ofs << this->contextSettings.antialiasingLevel << "\n";
    }

    ofs.close();
};

GraphicsSettings::~GraphicsSettings() = default;
