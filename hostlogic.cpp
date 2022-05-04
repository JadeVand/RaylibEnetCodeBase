#include <hostlogic.h>

HostLogic::HostLogic(){
   
}

void HostLogic::update(float deltatime){
    GameLogic::update(deltatime);
    
    if(updating){
        
    }
}
void HostLogic::draw(int screenWidth,int screenHeight){
    
}
void HostLogic::host(){
    interface.dedicatedconnect(true);
}
