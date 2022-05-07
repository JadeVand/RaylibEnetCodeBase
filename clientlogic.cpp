#include <clientlogic.h>

ClientLogic::ClientLogic(ENetInterface* interface,AbstractGame* game,bool host) : UndecidedLogic(interface,game,host){
    gamestate = std::make_shared<GameState>(this,2,1);
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
                
            }else if(header->signature == GAMESIGNATURE &&
                     header->packettype == kMove){
                //player client sent move packet
                
                if(obj->length>=sizeof(XoMovePacket)){
                    XoMovePacket mp = {0};
                    memcpy(&mp,obj->data,sizeof(XoMovePacket));
                    printf("move-%d:%d\n",mp.x,mp.y);
                    if(!trymoveremote(mp,gamestate->getapponent())){
                        /*
                         if we were host
                         here we would call
                         if(ishost()){
                         broadcast or reply
                         }
                         */
                    }else{
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
    
}
//this can probably just be uint32_t x, uint32_t y
//this is called from the network callback
bool ClientLogic::trymoveremote(const XoMovePacket& mp,Entity* e){
    printf("trymoveremote called\n");
    return gamestate->processmove(mp,e);
}
//this is called from the level
void ClientLogic::movebroadcast(uint32_t x, uint32_t y){
    UndecidedLogic::movebroadcast(x,y);
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
bool ClientLogic::ishost(){
    return host;
}
