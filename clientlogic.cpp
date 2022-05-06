#include <clientlogic.h>

ClientLogic::ClientLogic(ENetInterface* interface,AbstractGame* game) : UndecidedLogic(interface,game){

}
void ClientLogic::update(float deltatime){

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
                
                //BEGIN GAMEPLAY
                game->creategamelevelascurrentlogic();
            }else if(header->signature == NATSIGNATURE && header->packettype == kHostname){
                //We ignore this packet since we're not hosting
                
            }
            
        }
         
    };
    auto eventerror = [this](void){
        
    };
    interface->quecompletion(eventsuccess,eventerror,1);
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
std::shared_ptr<GameState> ClientLogic::getgamestate(){
    return gamestate;
}
void ClientLogic::creategamestate(){
    gamestate = std::make_shared<GameState>();
}
