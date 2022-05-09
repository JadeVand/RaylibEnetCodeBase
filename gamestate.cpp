#include <gamestate.h>

GameState::GameState(GameLogic* logic,uint32_t myxoid, uint32_t apponentxoid) {
    this->logic = logic;
    memset(map,0,sizeof(map));
    me.setxoid(myxoid);
    apponent.setxoid(apponentxoid);
    XoGridMap2D map2d = (XoGridMap2D)map;
    for(int x = 0; x < 3; ++x){
        for(int y= 0; y < 3; ++y){
            map2d[x][y]->x = x;
            map2d[x][y]->y = y;
            map2d[x][y]->occupied = false;
            map2d[x][y]->xoid = 0;
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


    XoGrid* block = NULL;
    if(!isxyvalid(x,y)){
        return false;
    }
    XoGridMap2D map2d = (XoGridMap2D)map;
    block = map2d[x][y];
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
void GameState::rejectmove(uint32_t x, uint32_t y, uint32_t xoid){
    if(!isxyvalid(x,y)){
        return;
    }
    XoGrid* block = NULL;
    XoGridMap2D mapd = (XoGridMap2D)map;
    block = mapd[x][y];
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
XoGridMap2D GameState::getmap(){
    return (XoGridMap2D)map;
}
