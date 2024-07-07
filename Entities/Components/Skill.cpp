#include "Skill.h"

Skill::Skill(SKILL type) : type(type) {
    this->level = 1;
    this->exp = 0;
    this->expNext = 100;
}

Skill::~Skill() {

}

void Skill::update() const {

}
