#include "Tilemap.h"

Tilemap::Tilemap(const std::string &file_name) {
    this->loadFromFile(file_name);
}

Tilemap::~Tilemap() {
    for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
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

void Tilemap::update() {

}

void Tilemap::render(sf::RenderTarget &target, Entity *entity) {
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
    if (index_x < this->maxSizeGrid.x && index_y < this->maxSizeGrid.y && index_z < this->layers) {
        delete this->map[index_x][index_y][index_z];
        this->map[index_x][index_y][index_z] = nullptr;
    }
}

void
Tilemap::addTile(const TileData &tileData) {
    if (tileData.index_x < this->maxSizeGrid.x && tileData.index_y < this->maxSizeGrid.y &&
        tileData.index_z < this->layers) {
        if (this->map[tileData.index_x][tileData.index_y][tileData.index_z] == nullptr) {
            this->map[tileData.index_x][tileData.index_y][tileData.index_z] = new Tile(
                    tileData.index_x * this->gridSizeF, tileData.index_y * this->gridSizeF, this->gridSizeF,
                    this->tileTextureSheet,
                    tileData.textureRect, tileData.types);
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

        // Basic Map Information
        file >> size.x >> size.y >> gridSizeU >> layers >> texturePath;

        this->gridSizeF = static_cast<float> (gridSizeU);
        this->gridSizeU = gridSizeU;
        this->maxSizeGrid.x = size.x;
        this->maxSizeGrid.y = size.y;
        this->maxSizeWorld.x = static_cast<float>(size.x * gridSizeU);
        this->maxSizeWorld.y = static_cast<float>(size.y * gridSizeU);
        this->layers = layers;
        this->texturePath = texturePath;

        this->clear();

        if (!this->tileTextureSheet.loadFromFile(this->texturePath)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME:" << this->texturePath << "\n";
        }

        this->map.resize(this->maxSizeGrid.x);
        for (int x = 0; x < this->maxSizeGrid.x; x++) {
            this->map[x].resize(this->maxSizeGrid.y);
            for (int y = 0; y < maxSizeGrid.y; y++) {
                //mappa vuota
                this->map[x][y].resize(this->layers, nullptr);
            }
        }

        // Load all Tiles
        std::string line;

        while (getline(file, line)) {
            TileData tileData;

            if (line.empty()) {
                continue;
            }
            std::istringstream iss(line);
            float tr_x, tr_y;
            iss >> tileData.index_x >> tileData.index_y >> tileData.index_z >> tr_x >> tr_y;
            tileData.textureRect = sf::Vector2f(tr_x, tr_y);
            int num;
            while (iss >> num) {
                tileData.types.push_back(static_cast<TILE_TYPES>(num));
            }
            this->addTile(tileData);
        }

    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE: " << file_name << "\n";
    }

    file.close();
}

void Tilemap::saveToFile(std::string file_name) {
    std::ofstream out_file;
    out_file.open(file_name, std::ofstream::out | std::ofstream::trunc);

    if (out_file.is_open()) {
        out_file << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << "\n";
        out_file << this->gridSizeU << "\n";
        out_file << this->layers << "\n";
        out_file << this->texturePath << "\n";

        for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
            for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
                for (size_t z = 0; z < this->layers; z++) {
                    if (this->map[x][y][z]) {
                        std::string pippo = this->map[x][y][z]->getAsString();
                        out_file << x << " " << y << " " << z << " " << pippo << "\n";
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
    for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
            for (size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
                this->map[x][y][z] = nullptr;
            }
        }
    }
}

std::tuple<bool, bool> Tilemap::checkCollision(const sf::RectangleShape &rectangleShape) const {
    return this->checkOutOfBounds(rectangleShape);
}

std::tuple<bool, bool> Tilemap::checkOutOfBounds(const sf::RectangleShape &rectangleShape) const {
    bool dir_x = rectangleShape.getGlobalBounds().left < 0 || rectangleShape.getGlobalBounds().left + rectangleShape.getSize().x > this->maxSizeWorld.x;
    bool dir_y = rectangleShape.getGlobalBounds().top < 0 || rectangleShape.getGlobalBounds().top + rectangleShape.getSize().y > this->maxSizeWorld.y;
    return std::make_tuple(dir_x, dir_y);
}



