#include <hostlogic.h>

HostLogic::HostLogic(ENetInterface* interface) : UndecidedLogic(interface){
    hostname = 0;
    failedtoconnect = false;
}

void HostLogic::update(float deltatime){
    GameLogic::update(deltatime);
    
    if(updating){
        
    }
    auto lambda = [this](uint8_t* data,size_t length, int result){
        handlenetforlevel(data,length,result);
    };
    interface->quecompletion(lambda,1);
}
void HostLogic::draw(int screenWidth,int screenHeight){
    

    if(hostname){
        ClearBackground(RAYWHITE);
        std::string hostnamestring = std::to_string(hostname);
        DrawText(TextFormat("Hostname: %p",hostname),screenWidth/2-100,screenHeight/2,20,RED);
    }else if(failedtoconnect){
        ClearBackground(RAYWHITE);
        std::string hostnamestring = std::to_string(hostname);
        DrawText(TextFormat("Unable to connect",hostname),screenWidth/2-100,screenHeight/2,20,RED);
    }
    
}
void HostLogic::host(){
    if(!interface->dedicatedconnect(true)){
        failedtoconnect = true;
    }
}
void HostLogic::send(uint8_t* packet,uint32_t size){
    
}
bool HostLogic::needstodraw(){
    if(hostname){
        return true;
    }else if(failedtoconnect){
        return true;
    }
    return false;
}
void HostLogic::handlenetforlevel(uint8_t* data,size_t length,int result){
    
}
