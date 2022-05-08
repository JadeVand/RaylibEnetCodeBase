#include <ingamelogic.h>

InGameLogic::InGameLogic(ENetInterface* interface,AbstractGame* game,bool host) : OutOfGameLogic(interface,game,host){
    hostname = 0;
    failedtoconnect = false;
    gamestate = std::make_shared<GameState>(this,1,2);
}

void InGameLogic::update(float deltatime){

    auto eventsuccess = [this](uint8_t* data, size_t dataLength){
        
        if(dataLength>=sizeof(PacketHeader)){
            
            PacketHeader* header = (PacketHeader*)data;
            if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                //We ignore this packet since it could be
                //left over holepunch packets in the stream
            }
            else if(header->signature == NATSIGNATURE && header->packettype == kHostname){
                HostPacket* hp = (HostPacket*)data;
                hostname = hp->hostname;
                
            }else if(header->signature == GAMESIGNATURE &&
                     header->packettype == kMove){
                //player client sent move packet
                
                if(dataLength>=sizeof(XoMovePacket)){
                    XoMovePacket mp = {0};
                    memcpy(&mp,data,sizeof(XoMovePacket));
                    printf("move-%d:%d\n",mp.x,mp.y);
                    if(!trymoveremote(mp,gamestate->getapponent())){
                        //move rejected let them know
                    }else{
                        //move accepted
                        //broadcast if needed
                    }
                }else{
                    //did someone manipulate the packet? BAD
                }
            }
            
        }
         
    };
    auto eventerror = [this](void){
        
    };
    interface->quecompletion(eventsuccess,eventerror,1);
}
void InGameLogic::draw(int screenWidth,int screenHeight){
    
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
bool InGameLogic::needstodraw(){
    if(hostname){
        return true;
    }else if(failedtoconnect){
        return true;
    }
    return false;
}

std::shared_ptr<GameState> InGameLogic::getgamestate(){
    return gamestate;
}
void InGameLogic::creategamestate(){
    //gamestate = std::make_shared<GameState>(this,1,2);
}
//this can probably just be uint32_t x, uint32_t y
//this is called from the network callback
bool InGameLogic::trymoveremote(const XoMovePacket& mp,Entity* e){
    return gamestate->processmove(mp,e);
}
//this is called from the level
void InGameLogic::movebroadcast(uint32_t x, uint32_t y){
    XoMovePacket mp = {0};
    mp.ph.signature = GAMESIGNATURE;
    mp.ph.packettype = kMove;
    mp.x = x;
    mp.y = y;
    if(trymoveremote(mp,gamestate->getself())){
        printf("called trymovebroadcast\n");
        interface->sendpacketnetwork((uint8_t*)&mp,sizeof(XoMovePacket));
    }
}
bool InGameLogic::ishost(){
    return host;
}
