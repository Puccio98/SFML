#pragma once

#include "../Weapon.h"

class MeleeWeapon : public Weapon {
private:
protected:


public:
    MeleeWeapon();

    ~MeleeWeapon() override;

    void attackEnemy(Entity *pEntity) override;
};



