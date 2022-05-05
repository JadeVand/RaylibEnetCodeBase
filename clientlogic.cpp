#include <clientlogic.h>

ClientLogic::ClientLogic(ENetInterface* interface,AbstractGame* game) : UndecidedLogic(interface,game){

}
void ClientLogic::update(float deltatime){

    if(updating){
        
    }
}

void ClientLogic::draw(int screenWidth,int screenHeight){
    
}
void ClientLogic::send(uint8_t* packet,uint32_t size){
    
}
bool ClientLogic::needstodraw(){
    return false;
}
void ClientLogic::handlenetforlevel(uint8_t* data,size_t length,int result){
    
}
