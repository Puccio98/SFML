#include "SkillComponent.h"

SkillComponent::SkillComponent() {
    this->skills.emplace(SKILL::WOOD_CUTTING, Skill(SKILL::WOOD_CUTTING));
    this->skills.emplace(SKILL::MINING, Skill(SKILL::MINING));
}

SkillComponent::~SkillComponent() = default;

void SkillComponent::update() {
    for (const auto &skill: this->skills) {
        skill.second.update();
    }
}

const Skill &SkillComponent::getSkill(const SKILL skill) {
    if (this->skills.count(skill) == 0) {
        throw ("ERROR::SKILLCOMPONENT::SKILL DOES NOT EXIST " + static_cast<int>(skill));
    }
    return this->skills.at(skill);
}
