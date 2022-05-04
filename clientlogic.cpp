#include <clientlogic.h>

ClientLogic::ClientLogic(ENetInterface* interface){
    this->interface = interface;
}
void ClientLogic::update(float deltatime){
    GameLogic::update(deltatime);
    
    if(updating){
        
    }
}

void ClientLogic::draw(int screenWidth,int screenHeight){
    
}
void ClientLogic::join(uint64_t hostname){
    interface->dedicatedconnect(hostname);
}
void ClientLogic::send(uint8_t* packet,uint32_t size){
    
}
