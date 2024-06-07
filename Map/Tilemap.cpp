#include "Tilemap.h"

Tilemap::Tilemap(const std::string &file_name, sf::Font &font) : font(font) {
    this->loadFromFile(file_name);
}

Tilemap::~Tilemap() {
    for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
            while (this->map[x][y].size() != 0) {
                delete this->map[x][y].at(this->map[x][y].size() - 1);
                this->map[x][y].pop_back();
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

void Tilemap::removeTile(const unsigned index_x, const unsigned index_y) {
    if (index_x < this->maxSizeGrid.x && index_y < this->maxSizeGrid.y && this->map[index_x][index_y].size() != 0) {
        int size = this->map[index_x][index_y].size();

        delete this->map[index_x][index_y].at(this->map[index_x][index_y].size() - 1);
        this->map[index_x][index_y].pop_back();
    }
}

void Tilemap::addTile(const TileData &tileData) {
    if (tileData.index_x < this->maxSizeGrid.x &&
        tileData.index_y < this->maxSizeGrid.y //&& tileData.index_z < this->layers
            ) {
        this->map[tileData.index_x][tileData.index_y].push_back(new Tile(
                tileData,
                this->tileTextureSheet,
                this->font));
    }
}

const sf::Texture &Tilemap::getTileTextureSheet() const {
    return tileTextureSheet;
}


void Tilemap::loadFromFile(const std::string file_name) {
    std::ifstream file;
    file.open(file_name);

    if (file.fail()) {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE: " << file_name << "\n";
        return;
    }

    if (file.is_open()) {
        // Skip the first row of the legend
        std::string _legenda;
        std::getline(file, _legenda);

        sf::Vector2u _size;
        unsigned _gridSizeU = 0;
        unsigned _layers = 0;
        std::string _texturePath;

        // Read max_size_grid
        std::string line;
        std::getline(file, line);
        {
            std::istringstream iss(line);
            std::string label;
            iss >> label >> _size.x >> _size.y;
        }

        // Read grid_size
        std::getline(file, line);
        {
            std::istringstream iss(line);
            std::string label;
            iss >> label >> _gridSizeU;
        }

        // Read max_layers
        std::getline(file, line);
        {
            std::istringstream iss(line);
            std::string label;
            iss >> label >> _layers;
        }

        // Read texture_path
        std::getline(file, line);
        {
            std::istringstream iss(line);
            std::string label;
            iss >> label >> _texturePath;
        }

        this->gridSizeF = static_cast<float>(_gridSizeU);
        this->gridSizeU = _gridSizeU;
        this->maxSizeGrid.x = _size.x;
        this->maxSizeGrid.y = _size.y;
        this->maxSizeWorld.x = static_cast<float>(_size.x * _gridSizeU);
        this->maxSizeWorld.y = static_cast<float>(_size.y * _gridSizeU);
        this->layers = _layers;
        this->texturePath = _texturePath;

        this->clear();

        if (!this->tileTextureSheet.loadFromFile(this->texturePath)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME:" << this->texturePath << "\n";
        }

        this->map.resize(this->maxSizeGrid.x);
        for (unsigned x = 0; x < this->maxSizeGrid.x; x++) {
            this->map[x].resize(this->maxSizeGrid.y);
            for (unsigned y = 0; y < this->maxSizeGrid.y; y++) {
                // Initialize empty map
                this->map[x][y] = std::vector<Tile *>();
                //this->map[x][y].resize(this->layers, nullptr);
            }
        }

        // Load all Tiles
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            this->loadTile(line);
        }
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE: " << file_name << "\n";
    }

    file.close();
}

void Tilemap::loadTile(const std::string &line) {
    TileData tileData;
    tileData.gridSize = this->gridSizeF;

    std::istringstream iss(line);

    // Parse the tile position (p x y z)
    std::string label;
    iss >> label >> tileData.index_x >> tileData.index_y >> tileData.index_z;

    // Parse the texture position (t_p x y), until "t_t" is reached
    iss >> label; // t_p
    std::string x;

    while (iss >> x) {
        std::string y;
        if (x == "t_t") {
            break;
        }
        iss >> y;
        if (y == "t_t") {
            break;
        }
        tileData.texturePositions.emplace_back(std::stof(x), std::stof(y));
    }

    // Parse the tile types (t_t ...)
    int intType;
    while (iss >> intType) {
        tileData.types.push_back(static_cast<TILE_TYPES>(intType));
    }

    addTile(tileData);
}

void Tilemap::saveToFile(std::string file_name) {
    std::ofstream out_file;
    out_file.open(file_name, std::ofstream::out | std::ofstream::trunc);

    if (out_file.is_open()) {
        out_file
                << "Legenda: p == position(x,y,z), t_p == vettore di texture position(x,y), t_t == vettore di tipi di tile \n";
        out_file << "max_size_grid " << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << "\n";
        out_file << "grid_size " << this->gridSizeU << "\n";
        out_file << "max_layers " << this->layers << "\n";
        out_file << "texture_path " << this->texturePath << "\n";

        for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
            for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
                for (size_t z = 0; z < this->map[x][y].size(); z++) {
                    out_file << this->map[x][y][z]->getAsString(x, y, z) << "\n";
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
            while (this->map[x][y].size() != 0) {
                delete this->map[x][y].at(this->map[x][y].size() - 1);
                this->map[x][y].pop_back();
            }
        }
    }
}

std::tuple<bool, bool>
Tilemap::checkCollision(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape) const {
    std::tuple<bool, bool> collided = this->checkOutOfBounds(nextShape);

    return checkTileCollision(currentShape, nextShape, collided);
}

std::tuple<bool, bool> Tilemap::checkOutOfBounds(const sf::RectangleShape &rectangleShape) const {
    sf::FloatRect rect = rectangleShape.getGlobalBounds();

    bool dir_x = rect.left < 0 || rect.left + rect.width > this->maxSizeWorld.x;
    bool dir_y = rect.top < 0 || rect.top + rect.height > this->maxSizeWorld.y;

    return std::make_tuple(dir_x, dir_y);
}

std::tuple<bool, bool>
Tilemap::checkTileCollision(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape,
                            const std::tuple<bool, bool> &collided) const {


    std::tuple<bool, bool> forbidden_directions = getForbiddenDirections(currentShape, nextShape, collided);

    if (!std::get<0>(forbidden_directions) && !std::get<1>(forbidden_directions)) {
        forbidden_directions = getForbiddenDirections(nextShape, nextShape, collided);
    }

    return forbidden_directions;
}

std::tuple<bool, bool>
Tilemap::getForbiddenDirections(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape,
                                const std::tuple<bool, bool> &collided) const {
    // per ora gestiamo solamente il piano terra.
    int layer = 0;
    std::tuple<bool, bool> forbidden_directions = collided;

    auto checkDirection = [&](int startX, int endX, int startY, int endY, bool isVertical) {
        for (int x = startX; x <= endX; ++x) {
            for (int y = startY; y <= endY; ++y) {
                auto tileLayers = map[x][y];
                if (tileLayers.size() > layer) {
                    Tile *tile = map[x][y][layer];
                    if (tile != nullptr && tile->isOfType(TILE_TYPES::COLLISION)) {
                        if (isVertical) {
                            forbidden_directions = std::make_tuple(std::get<0>(forbidden_directions), true);
                        } else {
                            forbidden_directions = std::make_tuple(true, std::get<1>(forbidden_directions));
                        }
                        return;
                    }
                }
            }
        }
    };


    sf::FloatRect currentRect = currentShape.getGlobalBounds();
    sf::FloatRect nextRect = nextShape.getGlobalBounds();

    // Check top & bottom
    float diff_y = nextRect.top - currentRect.top;
    if (diff_y != 0 && !std::get<1>(forbidden_directions)) {
        auto tiles = getCollisionBounds(currentShape, nextShape, 1);
        auto starting_tile = std::get<0>(tiles);
        auto ending_tile = std::get<1>(tiles);
        int startY = (diff_y > 0) ? ending_tile.y : starting_tile.y;
        checkDirection(starting_tile.x, ending_tile.x, startY, startY, true);
    }

    // Check right & left
    float diff_x = nextRect.left - currentRect.left;
    if (diff_x != 0 && !std::get<0>(forbidden_directions)) {
        auto tiles = getCollisionBounds(currentShape, nextShape, 0);
        auto starting_tile = std::get<0>(tiles);
        auto ending_tile = std::get<1>(tiles);
        int startX = (diff_x > 0) ? ending_tile.x : starting_tile.x;
        checkDirection(startX, startX, starting_tile.y, ending_tile.y, false);
    }

    return forbidden_directions;
}


sf::Vector2i Tilemap::getGridPosition(const sf::Vector2f &absolutePosition) const {
    int gridX = static_cast<int>(absolutePosition.x / this->gridSizeU);
    int gridY = static_cast<int>(absolutePosition.y / this->gridSizeU);

    return {gridX, gridY};
}

std::tuple<sf::Vector2i, sf::Vector2i>
Tilemap::getCollisionBounds(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape,
                            int dir) const {
    // dir 0 == horizontal, dir 1 == vertical

    sf::FloatRect currentRect = currentShape.getGlobalBounds();
    sf::FloatRect nextRect = nextShape.getGlobalBounds();
    sf::Vector2f starting_point;
    sf::Vector2f ending_point;

    if (dir == 0) { // horizontal
        starting_point = sf::Vector2f(nextRect.left, currentRect.top);
        ending_point = sf::Vector2f(nextRect.left + nextRect.width, currentRect.top + currentRect.height);
    } else { // vertical
        starting_point = sf::Vector2f(currentRect.left, nextRect.top);
        ending_point = sf::Vector2f(currentRect.left + currentRect.width, nextRect.top + nextRect.height);
    }

    sf::Vector2i starting_tile = getGridPosition(starting_point);
    sf::Vector2i ending_tile = getGridPosition(ending_point);

    return std::make_tuple(starting_tile, ending_tile);
}

std::vector<Tile *> *Tilemap::getTileLayers(int x, int y) {
    if (x >= this->map.size()) {
        return nullptr;
    }

    if (y >= this->map[x].size()) {
        return nullptr;
    }

    return &this->map[x][y];
}

const std::vector<std::vector<std::vector<Tile *>>> &Tilemap::getMap() const {
    return map;
}

void Tilemap::addTexture(int index_x, int index_y, const sf::Vector2f &texturePosition) {
    if (index_x < this->map.size() &&
        index_y < this->map[index_x].size() &&
        !this->map[index_x][index_y].empty() &&
        this->map[index_x][index_y][this->map[index_x][index_y].size() - 1] != nullptr) {

        this->map[index_x][index_y][this->map[index_x][index_y].size() - 1]->addTexture(this->tileTextureSheet,
                                                                                        texturePosition);
    }
}
