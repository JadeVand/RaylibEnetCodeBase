#include <clientlogic.h>

ClientLogic::ClientLogic(){
    
}
void ClientLogic::update(float deltatime){
    GameLogic::update(deltatime);
    
    if(updating){
        
    }
}

void ClientLogic::draw(int screenWidth,int screenHeight){
    
}
void ClientLogic::join(uint64_t hostname){
    interface.dedicatedconnect(hostname);
}
