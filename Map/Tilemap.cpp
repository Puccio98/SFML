#include "Tilemap.h"

Tilemap::Tilemap(float gridSize, unsigned width, unsigned height, sf::Texture &_tileTextureSheet) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->tileTextureSheet = _tileTextureSheet;

    this->map.resize(this->maxSize.x);
    for (int x = 0; x < this->maxSize.x; x++) {
        this->map[x].resize(this->maxSize.y);
        for (int y = 0; y < maxSize.y; y++) {
            // mappa default
            //this->map[x][y].resize(this->layers, new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
            //mappa vuota
            this->map[x][y].resize(this->layers, nullptr);
        }
    }
}

Tilemap::~Tilemap() {
    // Elimino tutte le tile
    for (auto &x: this->map) {
        for (auto &y: x) {
            for (auto &z: y) {
                delete z;
            }
        }
    }
}

void Tilemap::update() {

}

void Tilemap::render(sf::RenderTarget &target) {
    for (auto &x: this->map) {
        for (auto &y: x) {
            for (auto *z: y) {
                if (z != nullptr) {
                    z->render(target);
                }
            }
        }
    }
}

void Tilemap::removeTile(const unsigned index_x, const unsigned index_y, const unsigned index_z) {
    if (index_x < this->maxSize.x && index_y < this->maxSize.y && index_z < this->layers) {
        delete this->map[index_x][index_y][index_z];
        this->map[index_x][index_y][index_z] = nullptr;
    }
}

void
Tilemap::addTile(const unsigned index_x, const unsigned index_y, const unsigned index_z,
                 sf::Vector2f tileTexturePosition) {
    if (index_x < this->maxSize.x && index_y < this->maxSize.y && index_z < this->layers) {
        if (this->map[index_x][index_y][index_z] == nullptr) {
            this->map[index_x][index_y][index_z] = new Tile(index_x * this->gridSizeF, index_y * this->gridSizeF,
                                                            this->gridSizeF, this->tileTextureSheet,
                                                            tileTexturePosition);
        }
    }
}

const sf::Texture &Tilemap::getTileTextureSheet() const {
    return tileTextureSheet;
}



