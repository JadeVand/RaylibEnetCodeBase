
#include <outofgamelogic.h>
OutOfGameLogic::OutOfGameLogic(ENetInterface* interface, AbstractGame* game, bool host){
    this->interface = interface;
    this->game = game;
    this->host = host;
}
void OutOfGameLogic::update(float deltatime){
    auto eventsuccess = [this](std::unique_ptr<PacketObject> obj){
        
        if(obj->length>=sizeof(PacketHeader)){
            
            PacketHeader* header = (PacketHeader*)obj->data;
            if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                
            }else if(header->packettype == kPeerId&&header->signature == NATSIGNATURE){
                
                CustomENet natpeeraddress = {0};
                CustomENet remote = {0};
                memcpy(&natpeeraddress,obj->data+sizeof(PacketHeader),sizeof(CustomENet));
                interface->donat(&natpeeraddress);
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                game->creategamelevelasunknownlogic();
            }else if(header->signature == NATSIGNATURE && header->packettype == kMatched){
                
                MatchPacket* mp = (MatchPacket*)obj->data;
                CustomENet remoteaddress = {0};
                memcpy(&remoteaddress,&mp->host,sizeof(CustomENet));
                interface->donat(&mp->host);
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                if(mp->ishost){
                    game->creategamelevelashostlogic();
                }else{
                    game->creategamelevelasclientlogic();
                }
            }
        }
        
    };
    auto eventerror = [this](void){
        
    };
    interface->quecompletion(eventsuccess,eventerror,1);
     
}
void OutOfGameLogic::draw(int screenWidth,int screenHeight){
    
}
bool OutOfGameLogic::needstodraw(){
    return false;
}
bool OutOfGameLogic::ishost(){
    return host;
}
bool OutOfGameLogic::que(){
    return interface->dedicatedconnect(false);
}
bool OutOfGameLogic::hostgame(){
    return interface->dedicatedconnect(true);
}
bool OutOfGameLogic::join(uint64_t hostname){
    return interface->dedicatedconnect(hostname);
}
