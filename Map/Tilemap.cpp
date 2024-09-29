#include "Tilemap.h"

using json = nlohmann::json;

Tilemap::Tilemap(const std::string &file_name, sf::Font &font) : Tilemap(file_name, font, false) {
}

Tilemap::Tilemap(const std::string &file_name, sf::Font &font, bool hud) : mapData(font, hud) {
    this->loadFromFile(file_name);
}

Tilemap::~Tilemap() {

    for (size_t x = 0; x < this->mapData.maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->mapData.maxSizeGrid.y; y++) {
            while (this->mapData.tiles[x][y].size() != 0) {
                delete this->mapData.tiles[x][y].at(this->mapData.tiles[x][y].size() - 1);
                this->mapData.tiles[x][y].pop_back();
            }
            this->mapData.tiles[x][y].clear();
        }
        this->mapData.tiles[x].clear();
    }

    this->mapData.tiles.clear();
}

void Tilemap::update(sf::RenderTarget &target, EntityDimensionData &entity, float dt, std::vector<Entity *> &entities) {
    sf::IntRect area = getInteractiveArea(target, entity);
    int end_x = area.left + area.width;
    int end_y = area.top + area.height;

    for (int i = area.left; i <= end_x && i < this->mapData.tiles.size(); ++i) {
        for (int j = area.top; j <= end_y && j < this->mapData.tiles[i].size(); ++j) {
            for (auto &k: this->mapData.tiles[i][j]) {
                k->update(dt, entities);
            }
        }
    }
}

void Tilemap::renderLayer(sf::RenderTarget &target, EntityDimensionData &entity, unsigned layerIndex) {
    sf::IntRect area = getInteractiveArea(target, entity);
    int end_x = area.left + area.width;
    int end_y = area.top + area.height;

    for (int i = area.left; i <= end_x && i < this->mapData.tiles.size(); ++i) {
        for (int j = area.top; j <= end_y && j < this->mapData.tiles[i].size(); ++j) {
            size_t layers = this->mapData.tiles[i][j].size();
            if (layers > layerIndex) {
                Tile *z = this->mapData.tiles[i][j][layerIndex];
                z->render(target);
            }
        }
    }
}

sf::IntRect Tilemap::getInteractiveArea(sf::RenderTarget &target, EntityDimensionData &entity) {
    int bufferArea = 3;
    sf::Vector2f position = entity.position;
    int entityGridPosition_x = position.x / this->mapData.gridSizeF;
    int entityGridPosition_y = position.y / this->mapData.gridSizeF;

    sf::Vector2f viewSize = target.getView().getSize();
    int halfSizeGrid_x = (viewSize.x / 2.f) / this->mapData.gridSizeU;
    int halfSizeGrid_y = (viewSize.y / 2.f) / this->mapData.gridSizeU;

    auto calculateStartTile = [this](int entityGridPosition, int halfSizeGrid) -> int {
        int startTile = entityGridPosition - halfSizeGrid;
        return startTile <= 0 ? 0 : startTile;
    };

    auto calculateEndTile = [this](int entityGridPosition, int halfSizeGrid, float entitySize) -> int {
        int endTile = entityGridPosition + (int) (entitySize / this->mapData.gridSizeU) + halfSizeGrid;
        return endTile <= 0 ? 0 : endTile;
    };

    int startTile_x = calculateStartTile(entityGridPosition_x, halfSizeGrid_x);
    int endTile_x = calculateEndTile(entityGridPosition_x, halfSizeGrid_x, entity.size.x);

    int startTile_y = calculateStartTile(entityGridPosition_y, halfSizeGrid_y);
    int endTile_y = calculateEndTile(entityGridPosition_y, halfSizeGrid_y, entity.size.y);
    sf::IntRect area;
    area.left = startTile_x;
    area.width = endTile_x - startTile_x + bufferArea;
    area.top = startTile_y;
    area.height = endTile_y - startTile_y + bufferArea;
    return area;
}

void Tilemap::render(sf::RenderTarget &target) {
    for (int i = 0; i < this->mapData.tiles.size(); ++i) {
        for (int j = 0; j < this->mapData.tiles[i].size(); ++j) {
            this->renderTileLayer(i, j, target);
        }
    }
}

void Tilemap::renderTileLayer(int i, int j, sf::RenderTarget &target) {
    for (auto z: this->mapData.tiles[i][j]) {
        if (z != nullptr) {
            z->render(target);
        }
    }
};


void Tilemap::removeTile(const unsigned index_x, const unsigned index_y) {
    if (index_x < this->mapData.maxSizeGrid.x && index_y < this->mapData.maxSizeGrid.y &&
        this->mapData.tiles[index_x][index_y].size() != 0) {
        delete this->mapData.tiles[index_x][index_y].at(this->mapData.tiles[index_x][index_y].size() - 1);
        this->mapData.tiles[index_x][index_y].pop_back();
    }
}


void Tilemap::addTile(const TileData &tileData) {
    if (tileData.index_x < this->mapData.maxSizeGrid.x &&
        tileData.index_y < this->mapData.maxSizeGrid.y //&& tileData.index_z < this->mapData.maxLayerIndex
            ) {
        this->mapData.addTile(tileData);
    }
}


const sf::Texture &Tilemap::getTileTextureSheet() const {
    return this->mapData.tileTextureSheet;
}


void Tilemap::loadFromFile(const std::string file_name) {
    std::ifstream file;
    file.open(file_name);

    if (file.fail()) {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE: " << file_name << "\n";
        return;
    }

    if (file.is_open()) {
        json jsonMap;
        file >> jsonMap;  // Read and parse the JSON content from the file
        this->mapData.from_json(jsonMap);
    }

    file.close();
}

void Tilemap::saveToFile(std::string file_name) {
    this->setMaxLayer();

    std::ofstream out_file;
    out_file.open(file_name, std::ofstream::out | std::ofstream::trunc);

    if (out_file.is_open()) {
        out_file << this->mapData.to_json();
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE: " << file_name << "\n";
    }

    out_file.close();
}

void Tilemap::clear() {
    if (this->mapData.tiles.empty()) {
        return;
    }
    for (size_t x = 0; x < this->mapData.maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->mapData.maxSizeGrid.y; y++) {
            while (this->mapData.tiles[x][y].size() != 0) {
                delete this->mapData.tiles[x][y].at(this->mapData.tiles[x][y].size() - 1);
                this->mapData.tiles[x][y].pop_back();
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

    bool dir_x = rect.left < 0 || rect.left + rect.width > this->mapData.maxSizeWorld.x;
    bool dir_y = rect.top < 0 || rect.top + rect.height > this->mapData.maxSizeWorld.y;

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
                auto tileLayers = this->mapData.tiles[x][y];
                if (tileLayers.size() > layer) {
                    Tile *tile = this->mapData.tiles[x][y][layer];
                    if (tile != nullptr && tile->isOfType(TILE_BEHAVIOURS::COLLISION)) {
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
    return {static_cast<int>(absolutePosition.x / this->mapData.gridSizeU),
            static_cast<int>(absolutePosition.y / this->mapData.gridSizeU)};
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
    if (x >= this->mapData.tiles.size()) {
        return nullptr;
    }

    if (y >= this->mapData.tiles[x].size()) {
        return nullptr;
    }

    return &this->mapData.tiles[x][y];
}

const std::vector<std::vector<std::vector<Tile *>>> &Tilemap::getMap() const {
    return this->mapData.tiles;
}

void Tilemap::addTexture(int index_x, int index_y, const sf::Vector2f &texturePosition) {
    if (index_x < this->mapData.tiles.size() &&
        index_y < this->mapData.tiles[index_x].size() &&
        !this->mapData.tiles[index_x][index_y].empty() &&
        this->mapData.tiles[index_x][index_y][this->mapData.tiles[index_x][index_y].size() - 1] != nullptr) {

        this->mapData.tiles[index_x][index_y][this->mapData.tiles[index_x][index_y].size() - 1]->addTexture(
                this->mapData.tileTextureSheet,
                texturePosition);
    }
}

void Tilemap::setMaxLayer() {
    size_t layerIndex = 0;

    if (this->mapData.tiles.empty()) {
        this->mapData.maxLayerIndex = layerIndex;
        return;
    }
    for (size_t x = 0; x < this->mapData.maxSizeGrid.x; x++) {
        for (size_t y = 0; y < this->mapData.maxSizeGrid.y; y++) {
            if (this->mapData.tiles[x][y].size() > 1) {
                size_t layerIndexZ = this->mapData.tiles[x][y].size() - 1;
                layerIndex = layerIndex < layerIndexZ ? layerIndexZ : layerIndex;
            }
        }
    }

    this->mapData.maxLayerIndex = layerIndex;
}

unsigned int Tilemap::getMaxLayerIndex() const {
    return this->mapData.maxLayerIndex;
}

