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
bool GameState::processmove(const XoMovePacket& mp,Entity* e){

    printf("process move called\n");
    
    uint32_t y = mp.y;
    uint32_t x = mp.x;
    XoGrid* block = NULL;
    for(int n = 0; n < 9; ++n){
        if(map[n].x==x && map[n].y==y){
            block = &map[n];
            break;
        }
    }
    if(!block){
        return false;
    }
    printf("we got a block\n");
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
