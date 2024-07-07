#ifndef SFML_SKILLCOMPONENT_H
#define SFML_SKILLCOMPONENT_H


#include <string>
#include <map>
#include "Skill.h"

class SkillComponent {
private:
    std::map<SKILL, Skill> skills;
public:
    SkillComponent();

    virtual ~SkillComponent();

    void update();

    const Skill &getSkill(const SKILL skill);
};


#endif
