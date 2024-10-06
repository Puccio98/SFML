#include "AttributeComponent.h"

AttributeComponent::AttributeComponent() {
    this->hpMax = 24.f;
    this->hp = 24.f;
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