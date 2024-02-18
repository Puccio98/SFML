#include "Tilemap.h"

Tilemap::Tilemap() {
    this->gridSizeF = 50.f;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = 100;
    this->maxSize.y = 100;
    this->layers = 1;

    //TODO:: Verifica che emplace serva davvero, forse resize chiama il costruttore e basta quello
    this->map.resize(this->maxSize.x);
    for (int x = 0; x < this->maxSize.x; x++) {
        //this->map.emplace_back();

        this->map[x].resize(this->maxSize.y);
        for (int y = 0; y < maxSize.y; y++) {
            // this->map[x].emplace_back();

            this->map[x][y].resize(this->layers, Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
            // secondo me non serve a nulla il ciclo for su Z, almeno per ora
            //            for (int z = 0; z < layers; z++) {
//                this->map[x][y].emplace_back(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF);
//            }
        }
    }
}

Tilemap::~Tilemap() {

}

void Tilemap::update() {

}

void Tilemap::render(sf::RenderTarget &target) {
    for (auto &x: this->map) {
        for (auto &y: x) {
            for (auto &z: y) {
                z.render(target);
            }
        }
    }
}
