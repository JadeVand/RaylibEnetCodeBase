#include <ingamelogic.h>

InGameLogic::InGameLogic(ENetInterface* interface,AbstractGame* game,bool host) : OutOfGameLogic(interface,game,host){
    hostname = 0;
    if(host){
        gamestate = std::make_shared<GameState>(this,1,2);
    }else{
        gamestate = std::make_shared<GameState>(this,2,1);
    }
    processing = true;
    procstate = kProcessingStateNone;
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
                    //no authority check needs to be done
                    processmove(mp->x,mp->y, gamestate->getapponent());
                }else{
                    //did someone manipulate the packet? BAD
                }
            }
            
        }
         
    };
    auto eventerror = [this](void){
        
    };
    interface->quecompletion(eventsuccess,eventerror,0);
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
    std::vector<std::string> Buffer = {""};
}

std::shared_ptr<GameState> InGameLogic::getgamestate(){
    return gamestate;
}
void InGameLogic::creategamestate(){
    //gamestate = std::make_shared<GameState>(this,1,2);
}
bool InGameLogic::processmove(uint32_t x, uint32_t y,Entity* e){
    if(gamestate->processmove(x,y,e)){
        //
        //Check win logic here
        Entity* e = gamestate->getwinner();
        if(e){
            processing = false;
            if(e==gamestate->getself()){
                procstate = kProcessingStateWinner;
            }else{
                procstate = kProcessingStateLoser;
            }
            
        }else{
            if(gamestate->isgameover()){
                processing = false;
                procstate = kProcessingStateDraw;
            }
        }
        gamestate->swapturn();
        return true;
    }
    return false;
}
bool InGameLogic::processmovelocal(uint32_t x, uint32_t y){
    XoMovePacket mp = {0};
    mp.ph.signature = GAMESIGNATURE;
    mp.ph.packettype = kMove;
    mp.x = x;
    mp.y = y;
    if(processmove(x,y,gamestate->getself())){
        interface->sendpacketnetwork((uint8_t*)&mp,sizeof(XoMovePacket));
        return true;
    }
    return false;
}
bool InGameLogic::ishost(){
    return host;
}
bool InGameLogic::isprocessing(){
    return processing;
}

uint16_t InGameLogic::getstatusforgameplay(){
    return procstate;
}
