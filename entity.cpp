#include <entity.h>

Entity::Entity(){
    choice = 0;
}
void Entity::SetChoice(int choice){
    this->choice = choice;
}
int Entity::GetChoice(){
    return choice;
}
