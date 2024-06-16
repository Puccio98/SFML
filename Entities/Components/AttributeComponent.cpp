#include "AttributeComponent.h"

AttributeComponent::AttributeComponent() {
    this->hpMax = 30.f;
    this->hp = 10.f;

}

AttributeComponent::~AttributeComponent() {
}

float AttributeComponent::getHpMax() const {
    return hpMax;
}

float AttributeComponent::getHp() const {
    return hp;
}

