//
// Created by malte on 07/07/2024.
//

#include "Item.h"

Item::Item() {

}

Item::~Item() {
    delete this->animationComponent;
    delete this->hitboxComponent;
}