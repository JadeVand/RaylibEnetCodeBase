#include <gamestate.h>

GameState::GameState(GameLogic* logic,uint32_t myxoid, uint32_t apponentxoid) {
    this->logic = logic;
    memset(map,0,sizeof(map));
    me.setxoid(myxoid);
    apponent.setxoid(apponentxoid);
    for(int x = 0; x < 3; ++x){
        for(int y= 0; y < 3; ++y){
            map[x][y].x = x;
            map[x][y].y = y;
            map[x][y].occupied = false;
            map[x][y].xoid = 0;
        }
    }
}
bool GameState::isxyvalid(uint32_t x, uint32_t y){
    if(x>2||y>2){//this check might result in a crash at some point bceause maybe x and y can be less than 0? idk
        return false;
    }
    return true;
}
bool GameState::processmove(uint32_t x, uint32_t y,Entity* e){


    if(turn!=e){
        return false;
    }
    XoGrid* block = NULL;
    if(!isxyvalid(x,y)){
        return false;
    }
    block = &map[x][y];
    if(!block){
        return false;
    }
    if(block->occupied){
        return false;
    }
    
    block->occupied = true;
    block->xoid = e->getxoid();
    

    return true;
}
void GameState::swapturn(){
    if(turn==&me){
        turn = &apponent;
    }else{
        turn = &me;
    }
}
void GameState::rejectmove(uint32_t x, uint32_t y, uint32_t xoid){
    if(!isxyvalid(x,y)){
        return;
    }
    XoGrid* block = NULL;
    block = &map[x][y];
    block->xoid = xoid;
}
bool GameState::checkwinner(uint32_t xoid){
    return false;
}
Entity* GameState::getself(){
    return &me;
}
Entity* GameState::getapponent(){
    return &apponent;
}
void GameState::setturn(Entity* t){
    turn = t;
}
/*
XoGridMap2D GameState::getmap(){
    return (XoGridMap2D)map;
}
 */
bool GameState::isoccupied(uint32_t x, uint32_t y){
    if(map[x][y].occupied){
        return true;
    }
    return false;
}
uint32_t GameState::getidforxy(uint32_t x,uint32_t y){
    return map[x][y].xoid;
}
