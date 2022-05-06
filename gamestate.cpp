#include <gamestate.h>

GameState::GameState(){
    memset(map,0,sizeof(map));
}
bool GameState::processmove(const XoMovePacket& mp){
    
}
bool GameState::checkwinner(uint32_t xoid){
    return false;
}
