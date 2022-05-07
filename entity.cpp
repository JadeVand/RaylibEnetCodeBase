#include <entity.h>

Entity::Entity(){
    xoid = 0;
}
void Entity::setxoid(uint32_t xoid){
    this->xoid = xoid;
}
uint32_t Entity::getxoid(){
    return xoid;
}
