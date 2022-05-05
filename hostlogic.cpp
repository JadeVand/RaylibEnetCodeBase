#include <hostlogic.h>

HostLogic::HostLogic(ENetInterface* interface,AbstractGame* game) : UndecidedLogic(interface,game){
    hostname = 0;
    failedtoconnect = false;
}

void HostLogic::update(float deltatime){

    if(updating){
        
    }
    auto eventsuccess = [this](std::unique_ptr<PacketObject> obj){
        
        if(obj->length>=sizeof(PacketHeader)){
            
            PacketHeader* header = (PacketHeader*)obj->data;
            if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                
            }
            else if(header->packettype == kPeerId&&header->signature == NATSIGNATURE){
                ENetAddress natpeeraddress = {0};
                CustomENet remote = {0};
                memcpy(&remote,obj->data+sizeof(PacketHeader),sizeof(CustomENet));
                memcpy(&natpeeraddress,&remote.host,sizeof(ENetAddress));
                interface->donat(&natpeeraddress);
                //printf("nat completed\n");
            }else if(header->signature == NATSIGNATURE && header->packettype == kHostname){
                HostPacket* hp = (HostPacket*)obj->data;
                hostname = hp->hostname;
                
            }
            
        }
         
    };
    auto eventerror = [this](void){
        
    };
    interface->quecompletion(eventsuccess,eventerror,1);
}
void HostLogic::draw(int screenWidth,int screenHeight){
    

    if(hostname){
        ClearBackground(RAYWHITE);
        std::string hostnamestring = std::to_string(hostname);
        DrawText(TextFormat("Hostname: %p",hostname),screenWidth/2-150,screenHeight/2,20,RED);
        DrawText(TextFormat("Give this to your apponent",hostname),screenWidth/2-150,screenHeight/2+30,20,RED);
    }else if(failedtoconnect){
        ClearBackground(RAYWHITE);
        std::string hostnamestring = std::to_string(hostname);
        DrawText(TextFormat("Unable to connect",hostname),screenWidth/2-100,screenHeight/2,20,RED);
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
