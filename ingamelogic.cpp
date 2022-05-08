#include <ingamelogic.h>

InGameLogic::InGameLogic(ENetInterface* interface,AbstractGame* game,bool host) : OutOfGameLogic(interface,game,host){
    hostname = 0;
    failedtoconnect = false;
    if(host){
        gamestate = std::make_shared<GameState>(this,1,2);
    }else{
        gamestate = std::make_shared<GameState>(this,2,1);
    }
    
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
                    XoMovePacket* mp = (XoMovePacket*)data;
                    if(!trymoveremote(mp->x,mp->y,gamestate->getapponent())){
                        //move rejected let them know
                        RejectionMovePacket rmp = {0};
                        
                        if(gamestate->isxyvalid(mp->x,mp->y)){
                            rmp.ph.signature = GAMESIGNATURE;
                            rmp.ph.packettype = kRejection;
                            rmp.x = mp->x;
                            rmp.y = mp->y;
                            typedef XoGrid map2d[3][3];
                            
                            XoGrid* map = gamestate->getmap();
                            map2d* dmap = (map2d*)map;
                            rmp.xoid =  dmap[mp->x][mp->y]->xoid;
                        }
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
bool InGameLogic::trymoveremote(uint32_t x, uint32_t y,Entity* e){
    
    if(!gamestate->processmove(x,y,e)){
        //send a rejection
        return false;
    }
    return true;
}

bool InGameLogic::trymovelocal(uint32_t x, uint32_t y,Entity* e){
    return gamestate->processmove(x,y,e);
}
//this is called from the level
void InGameLogic::movebroadcast(uint32_t x, uint32_t y){
    
    XoMovePacket mp = {0};
    mp.ph.signature = GAMESIGNATURE;
    mp.ph.packettype = kMove;
    mp.x = x;
    mp.y = y;
     
    if(trymovelocal(x,y,gamestate->getself())){
        printf("called trymovebroadcast\n");
        interface->sendpacketnetwork((uint8_t*)&mp,sizeof(XoMovePacket));
    }
}
bool InGameLogic::ishost(){
    return host;
}
