#include "Tilemap.h"

#include <utility>

Tilemap::Tilemap(const std::string &file_name) {
    this->loadFromFile(file_name);
}

Tilemap::~Tilemap() {
    this->clear();
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
                 sf::Vector2f tileTexturePosition, std::vector<TILE_TYPES>& tileTypes) {
    if (index_x < this->maxSize.x && index_y < this->maxSize.y && index_z < this->layers) {
        if (this->map[index_x][index_y][index_z] == nullptr) {
            this->map[index_x][index_y][index_z] = new Tile(
                    index_x * this->gridSizeF, index_y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet,
                    tileTexturePosition, tileTypes);
        }
    }
}

const sf::Texture &Tilemap::getTileTextureSheet() const {
    return tileTextureSheet;
}

void Tilemap::loadFromFile(const std::string file_name) {
    std::ifstream file;
    file.open(file_name);

    if (file.fail()) {
        return;
    }

    if (file.is_open()) {
        sf::Vector2u size;
        unsigned gridSizeU = 0;
        unsigned layers = 0;
        std::string texturePath;
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned textureRectX = 0;
        unsigned textureRectY = 0;
        bool collision = false;
        short type = 0;

        // Basic Map Information
        file >> size.x >> size.y >> gridSizeU >> layers >> texturePath;

        this->gridSizeF = static_cast<float> (gridSizeU);
        this->gridSizeU = gridSizeU;
        this->maxSize.x = size.x;
        this->maxSize.y = size.y;
        this->layers = layers;
        this->texturePath = texturePath;

        this->clear();

        if (!this->tileTextureSheet.loadFromFile(this->texturePath)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME:" << this->texturePath << "\n";
        }

        this->map.resize(this->maxSize.x);
        for (int x = 0; x < this->maxSize.x; x++) {
            this->map[x].resize(this->maxSize.y);
            for (int y = 0; y < maxSize.y; y++) {
                //mappa vuota
                this->map[x][y].resize(this->layers, nullptr);
            }
        }

        // Load all Tiles
        while (file >> x >> y >> z >> textureRectX >> textureRectY >> collision >> type) {
            //TODO: rivedere nel file la gestione dei tipi tile
            std::vector<TILE_TYPES> tileTypes;
            tileTypes.push_back(static_cast<TILE_TYPES>(type));
            this->addTile(x, y, z, sf::Vector2f(textureRectX, textureRectY), tileTypes);
        }
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE: " << file_name << "\n";
    }

    file.close();
}

void Tilemap::saveToFile(std::string file_name) {
    std::ofstream out_file;
    out_file.open(file_name);

    if (out_file.is_open()) {
        out_file << this->maxSize.x << " " << this->maxSize.y << "\n";
        out_file << this->gridSizeU << "\n";
        out_file << this->layers << "\n";
        out_file << this->texturePath << "\n";

        for (size_t x = 0; x < this->maxSize.x; x++) {
            for (size_t y = 0; y < this->maxSize.y; y++) {
                for (size_t z = 0; z < this->layers; z++) {
                    if (this->map[x][y][z]) {
                        out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
                    }
                }
            }
        }
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE: " << file_name << "\n";
    }

    out_file.close();
}

void Tilemap::clear() {
    if (this->map.empty()) {
        return;
    }
    for (size_t x = 0; x < this->maxSize.x; x++) {
        for (size_t y = 0; y < this->maxSize.y; y++) {
            for (size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
                this->map[x][y][z] = nullptr;
            }
            this->map[x][y].clear();
        }
        this->map[x].clear();
    }

    this->map.clear();
}



