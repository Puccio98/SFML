#ifndef SFML_MELEEWEAPON_H
#define SFML_MELEEWEAPON_H

#include "../Weapon.h"

class MeleeWeapon : public Weapon {
private:
protected:


public:
    MeleeWeapon();

    ~MeleeWeapon() override;

    void attackEnemy(Entity *pEntity) override;
};


#endif
