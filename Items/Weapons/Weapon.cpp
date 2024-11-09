#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::~Weapon() {

}

void Weapon::setPlayerFacingDirection(const std::pair<std::optional<DIRECTIONS>, DIRECTIONS> &playerFacingDirection) {
    Weapon::playerFacingDirection = playerFacingDirection;
}
