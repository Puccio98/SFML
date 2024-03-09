#include "Tilemap.h"

Tilemap::Tilemap(float gridSize, unsigned width, unsigned height) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(gridSize), static_cast<int>(gridSize));

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

    if (!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png")) {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET\n";
    }
}

const sf::Texture &Tilemap::getTileTextureSheet() const {
    return tileTextureSheet;
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

void Tilemap::addTile(const unsigned index_x, const unsigned index_y, const unsigned index_z) {
    if (index_x < this->maxSize.x && index_y < this->maxSize.y && index_z < this->layers) {
        if (this->map[index_x][index_y][index_z] == nullptr) {
            this->map[index_x][index_y][index_z] = new Tile(index_x * this->gridSizeF, index_y * this->gridSizeF,
                                                            this->gridSizeF, this->tileTextureSheet, this->textureRect);
        }
    }
}

void Tilemap::changeTile() {
    int tileSize = 50; //TODO: sistema questa variabile poi
    int width = this->tileTextureSheet.getSize().x;
    int height = this->tileTextureSheet.getSize().y;
    int originalHorizontalPosition = this->textureRect.left / tileSize;
    int originalVerticalPosition = this->textureRect.top / tileSize;
    int lastHorizontalPosition = width / tileSize;
    int lastVerticalPosition = height / tileSize;
    int nextHorizontalPosition = (originalHorizontalPosition + 1) % lastHorizontalPosition;
    if (nextHorizontalPosition == 0) {
        int nextVerticalPosition = (originalVerticalPosition + 1) % lastVerticalPosition;
        this->textureRect.top = nextVerticalPosition * tileSize;
    }
    this->textureRect.left = nextHorizontalPosition * tileSize;

    //TODO: aggiungere preview tile
}

const sf::IntRect &Tilemap::getTextureRect() const {
    return textureRect;
}
