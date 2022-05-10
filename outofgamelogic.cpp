
#include <outofgamelogic.h>
OutOfGameLogic::OutOfGameLogic(ENetInterface* interface, AbstractGame* game, bool host){
    this->interface = interface;
    this->game = game;
    this->host = host;
    mms = kMatchMakingStatusNone;
    peerid = 0;
    displaytickforstatus = 0;
    totaldisplaytime = 10000;
}
void OutOfGameLogic::update(float deltatime){
    
    auto eventsuccess = [this](uint8_t* data, size_t dataLength){
        
        if(dataLength>=sizeof(PacketMatchmaking)){
            
            PacketMatchmaking* pmm = (PacketMatchmaking*)data;
            if(pmm->ph.signature == GAMESIGNATURE && pmm->ph.packettype == kNatReserved){
                
            }else if(pmm->ph.signature == NATSIGNATURE && pmm->ph.packettype == kPidPeerId){
                /*
                 *This is called in case the player hit host/join
                 */
                interface->donat(&pmm->address);
                
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                game->creategamelevelasunknownlogic();
            }else if(pmm->ph.signature == NATSIGNATURE && pmm->ph.packettype == kPidMatched){
                /*
                 *This is called in case the player hit queue
                 */
                interface->donat(&pmm->address);
                
                
                
                //NAT COMPLETED
                
                //BEGIN GGAMEPLAY
                if(pmm->extra){
                    game->creategamelevelashostlogic();
                }else{
                    game->creategamelevelasclientlogic();
                }
            }else if(pmm->ph.signature == NATSIGNATURE && pmm->ph.packettype == kPidHostName){
                peerid = pmm->peerid;
                mms = kMatchMakingStatusHostName;
                
            }else if(pmm->ph.signature == NATSIGNATURE && pmm->ph.packettype == kPidBadHostName){
                
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
bool OutOfGameLogic::join(uint32_t hostname){
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


uint32_t OutOfGameLogic::getpeerid(){
    return peerid;
}

bool OutOfGameLogic::displaystatus(){
    uint64_t now = getmstimeu64();
    return (now - displaytickforstatus < totaldisplaytime);
}
