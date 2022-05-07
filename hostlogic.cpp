#include <hostlogic.h>

HostLogic::HostLogic(ENetInterface* interface,AbstractGame* game,bool host) : UndecidedLogic(interface,game,host){
    hostname = 0;
    failedtoconnect = false;
    gamestate = std::make_shared<GameState>(this,1,2);
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
                
            }else if(header->signature == GAMESIGNATURE &&
                     header->packettype == kMove){
                //player client sent move packet
                
                if(obj->length>=sizeof(XoMovePacket)){
                    XoMovePacket mp = {0};
                    memcpy(&mp,obj->data,sizeof(XoMovePacket));
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

std::shared_ptr<GameState> HostLogic::getgamestate(){
    return gamestate;
}
void HostLogic::creategamestate(){
    //gamestate = std::make_shared<GameState>(this,1,2);
}
//this can probably just be uint32_t x, uint32_t y
//this is called from the network callback
bool HostLogic::trymoveremote(const XoMovePacket& mp,Entity* e){
    return gamestate->processmove(mp,e);
}
//this is called from the level
void HostLogic::movebroadcast(uint32_t x, uint32_t y){
    XoMovePacket mp = {0};
    mp.ph.signature = GAMESIGNATURE;
    mp.ph.packettype = kMove;
    mp.x = x;
    mp.y = y;
    if(trymoveremote(mp,gamestate->getself())){
        interface->sendpacketnetwork((uint8_t*)&mp,sizeof(XoMovePacket));
    }
}
bool HostLogic::ishost(){
    return host;
}
