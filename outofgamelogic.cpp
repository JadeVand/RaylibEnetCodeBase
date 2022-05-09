
#include <outofgamelogic.h>
OutOfGameLogic::OutOfGameLogic(ENetInterface* interface, AbstractGame* game, bool host){
    this->interface = interface;
    this->game = game;
    this->host = host;
    mms = kMatchMakingStatusNone;
    hostname = 0;
    displaytickforstatus = 0;
}
void OutOfGameLogic::update(float deltatime){
    
    auto eventsuccess = [this](uint8_t* data, size_t dataLength){
        
        if(dataLength>=sizeof(PacketHeader)){
            
            PacketHeader* header = (PacketHeader*)data;
            if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                
            }else if(header->packettype == kPeerId&&header->signature == NATSIGNATURE){
                
                CustomENet natpeeraddress = {0};
                CustomENet remote = {0};
                memcpy(&natpeeraddress,data+sizeof(PacketHeader),sizeof(CustomENet));
                interface->donat(&natpeeraddress);
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                game->creategamelevelasunknownlogic();
            }else if(header->signature == NATSIGNATURE && header->packettype == kMatched){
                
                MatchPacket* mp = (MatchPacket*)data;
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
            }else if(header->signature == NATSIGNATURE && header->packettype == kHostname){
                HostPacket* hp = (HostPacket*)data;
                if(dataLength>=sizeof(HostPacket)){
                    hostname = hp->hostname;
                    mms = kMatchMakingStatusHostName;
                }
                
            }else if(header->signature == NATSIGNATURE && header->packettype == kBadHostName){
                
                displaytickforstatus = getmstimeu64();
                mms = kMatchMakingStatusBadHostName;
            }
        }
        
    };
    auto eventerror = [this](void){

    };
    interface->quecompletion(eventsuccess,eventerror,1);
     
}
void OutOfGameLogic::draw(int screenWidth,int screenHeight){
    
}
bool OutOfGameLogic::ishost(){
    return host;
}
bool OutOfGameLogic::que(){
    if(!interface->dedicatedconnect(false)){
        mms = kMatchMakingStatusFailedConnection;
        return false;
    }
    return true;
}
bool OutOfGameLogic::hostgame(){
    if(!interface->dedicatedconnect(true)){
        mms = kMatchMakingStatusFailedConnection;
        return false;
    }
    return true;
}
bool OutOfGameLogic::join(uint64_t hostname){
    if(!interface->dedicatedconnect(hostname)){
        displaytickforstatus = getmstimeu64();
        mms = kMatchMakingStatusFailedConnection;
        return false;
    }
    return true;
}
uint16_t OutOfGameLogic::getstatusforgameplay(){
    return mms;
}

uint64_t OutOfGameLogic::gethostname(){
    return hostname;
}

bool OutOfGameLogic::displaystatus(){
    uint64_t now = getmstimeu64();
    return (now - displaytickforstatus < 10000);
}
