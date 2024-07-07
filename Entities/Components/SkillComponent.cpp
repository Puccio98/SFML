#include "SkillComponent.h"

SkillComponent::SkillComponent() {
    this->skills["wood_cutting"];
    this->skills["mining"];
}

SkillComponent::~SkillComponent() {

}

void SkillComponent::update() {
    for (const auto &skill: this->skills) {
        skill.second.update();
    }
}

const Skill &SkillComponent::getSkill(const std::string &key) {
    if (this->skills.count(key) == 0) {
        throw ("ERROR::SKILLCOMPONENT::SKILL DOES NOT EXIST " + key);
    }
    return this->skills[key];
}
