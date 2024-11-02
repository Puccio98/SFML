#include "AttributeComponent.h"

AttributeComponent::AttributeComponent()
        : AttributeComponent(24.f) { // Delegate to the parameterized constructor
}

AttributeComponent::AttributeComponent(float hp) {
    this->hpMax = hp;
    this->hp = hp;
}

AttributeComponent::~AttributeComponent() {
}

float AttributeComponent::getHpMax() const {
    return hpMax;
}

float AttributeComponent::getHp() const {
    return hp;
}

void AttributeComponent::applyDamage(float damage) {
    // Ensure health doesn't go below zero
    this->hp -= damage;
    if (this->hp < 0.f) {
        this->hp = 0.f;
    }
}

void AttributeComponent::restoreHealth(float amount) {
    // Increase hp but ensure it doesn't exceed hpMax
    this->hp += amount;
    if (this->hp > this->hpMax) {
        this->hp = this->hpMax;
    }
}

bool AttributeComponent::isDead() const {
    return this->hp <= 0.f;
}
