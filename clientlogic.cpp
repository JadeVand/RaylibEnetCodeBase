#include <clientlogic.h>

ClientLogic::ClientLogic(ENetInterface* interface) : UndecidedLogic(interface){

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
bool ClientLogic::needstodraw(){
    return false;
}
void ClientLogic::handlenetforlevel(uint8_t* data,size_t length,int result){
    
}
