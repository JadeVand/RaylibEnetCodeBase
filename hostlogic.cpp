#include <hostlogic.h>

HostLogic::HostLogic(ENetInterface* interface) : UndecidedLogic(interface){
    hostname = 0;
}

void HostLogic::update(float deltatime){
    GameLogic::update(deltatime);
    
    if(updating){
        
    }
    auto lambda = [this](uint8_t* data,size_t length, int result){
        if(length>=sizeof(PacketHeader)+sizeof(uint64_t)){
            PacketHeader* ph = (PacketHeader*)data;
            if(ph->packettype = kHostname&&ph->signature == NATSIGNATURE){
                
                HostPacket* hp = (HostPacket*)data;
                hostname = hp->hostname;
                printf("%p\n",hostname);
            }
            
        }
        //printf("packet size%d\n",length);
    };
    interface->quecompletion(lambda,1);
}
void HostLogic::draw(int screenWidth,int screenHeight){
    

    if(hostname){
        ClearBackground(RAYWHITE);
        std::string hostnamestring = std::to_string(hostname);
        DrawText(TextFormat("Hostname: %p",hostname),screenWidth/2-100,screenHeight/2,20,RED);
    }
    
}
void HostLogic::host(){
    interface->dedicatedconnect(true);
}
void HostLogic::send(uint8_t* packet,uint32_t size){
    
}
bool HostLogic::needstodraw(){
    if(hostname){
        return true;
    }
    return false;
}
