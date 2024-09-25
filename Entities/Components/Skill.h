#ifndef SFML_SKILL_H
#define SFML_SKILL_H

#include "../../enums/skill_enum.cpp"

class Skill {
private:
    int level;
    int exp;
    int expNext;
    SKILL type;

public:
    Skill(SKILL type);

    virtual ~Skill();

    void update() const;
};


#endif //SFML_SKILL_H
