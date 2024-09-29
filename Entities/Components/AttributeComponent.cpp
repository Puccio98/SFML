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

