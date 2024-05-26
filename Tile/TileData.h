#include <stack>

struct TileData {
    int index_x, index_y, index_z;
    /**
     * Definisce le posizioni della texture nello sheet, quindi determina la texture da applicare
     */
    std::vector<sf::Vector2f> texturePositions;
    std::vector<TILE_TYPES> types;
};

