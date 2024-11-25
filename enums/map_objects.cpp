/**
 * Questo deve diventare map_object type e deve indicare nel json se stiamo parlando di una tile, enemy spawner o element (tipo ooffe machine)o altro ancora
 */
enum class MAP_OBJECTS {
    TILE = 0,
    SPAWNER = 1,
    ELEMENT = 2,
    WARP = 3
};