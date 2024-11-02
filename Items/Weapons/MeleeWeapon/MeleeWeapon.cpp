#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon() = default;

MeleeWeapon::~MeleeWeapon() = default;

void MeleeWeapon::attackEnemy(Entity *pEntity) {
    if (pEntity == nullptr) {
        return;
    }

    if (!pEntity->isInvincible() &&
        this->hitboxComponent->checkIntersect(pEntity->getHitboxComponent()->getHitbox().getGlobalBounds())) {
        pEntity->takeDamage();
    }
}
