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
                //We ignore this packet since it could be
                //left over holepunch packets in the stream
            }
            else if(header->packettype == kPeerId&&header->signature == NATSIGNATURE){
                
                CustomENet natpeeraddress = {0};
                CustomENet remote = {0};
                memcpy(&natpeeraddress,obj->data+sizeof(PacketHeader),sizeof(CustomENet));
                interface->donat(&natpeeraddress);
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                game->creategamelevelascurrentlogic();
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
    
/*
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
    */
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
