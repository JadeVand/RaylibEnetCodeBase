#include <gamestate.h>

GameState::GameState(GameLogic* logic,uint32_t myxoid, uint32_t apponentxoid) {
    this->logic = logic;
    memset(map,0,sizeof(map));
    me.setxoid(myxoid);
    apponent.setxoid(apponentxoid);

    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            map[3*x + y].x = x;
            map[3*x + y].y = y;
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
    typedef XoGrid map2d[3][3];
    map2d* dmap = (map2d*)map;
    block = dmap[x][y];
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
XoGrid* GameState::getmap(){
    return map;
}
