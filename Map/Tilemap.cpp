#include "Tilemap.h"

Tilemap::Tilemap(float gridSize, unsigned width, unsigned height) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;

    //TODO:: Verifica che emplace serva davvero, forse resize chiama il costruttore e basta quello
    this->map.resize(this->maxSize.x);
    for (int x = 0; x < this->maxSize.x; x++) {
        //this->tilemap.emplace_back();

        this->map[x].resize(this->maxSize.y);
        for (int y = 0; y < maxSize.y; y++) {
            // this->tilemap[x].emplace_back();

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

void Tilemap::removeTile() {

}

void Tilemap::addTile() {

}
