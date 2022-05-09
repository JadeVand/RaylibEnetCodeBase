#include <ingamelogic.h>

InGameLogic::InGameLogic(ENetInterface* interface,AbstractGame* game,bool host) : OutOfGameLogic(interface,game,host){
    if(host){
        gamestate = std::make_shared<GameState>(this,1,2);
    }else{
        gamestate = std::make_shared<GameState>(this,2,1);
    }
    processing = true;
    mms = kMatchMakingStatusNone;
}

void InGameLogic::update(float deltatime){

    if(processing){//game is running
        auto eventsuccess = [this](uint8_t* data, size_t dataLength){
            
            if(dataLength>=sizeof(PacketHeader)){
                
                PacketHeader* header = (PacketHeader*)data;
                if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                    //We ignore this packet since it could be
                    //left over holepunch packets in the stream
                }
                else if(header->signature == GAMESIGNATURE &&
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
    
}
void InGameLogic::draw(int screenWidth,int screenHeight){

}

std::shared_ptr<GameState> InGameLogic::getgamestate(){
    return gamestate;
}
void InGameLogic::creategamestate(){
    //gamestate = std::make_shared<GameState>(this,1,2);
}
bool InGameLogic::processmove(uint16_t x, uint16_t y,Entity* e){
    if(gamestate->processmove(x,y,e)){
        //
        //Check win logic here
        Entity* e = gamestate->getwinner();
        if(e){
            displaytickforstatus = getmstimeu64();
            processing = false;
            if(e==gamestate->getself()){
                
                mms = kMatchMakingStateWinner;
            }else{
                mms = kMatchMakingStateLoser;
            }
            
        }else{
            if(gamestate->isgameover()){
                processing = false;
                mms = kMatchMakingStateDraw;
            }
        }
        gamestate->swapturn();
        return true;
    }
    return false;
}
bool InGameLogic::processmovelocal(uint16_t x, uint16_t y){
    if(processing){
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
    return true;
}
bool InGameLogic::ishost(){
    return host;
}
