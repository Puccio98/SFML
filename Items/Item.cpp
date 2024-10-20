#include "Item.h"

Item::Item() {

}

Item::~Item() {
    delete this->animationComponent;
    delete this->hitboxComponent;
}