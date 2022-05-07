#ifndef _undecidedlogic_h
#define _undecidedlogic_h
#include <gamestate.h>
class UndecidedLogic : public GameLogic{
protected:
    bool host;
    std::shared_ptr<GameState> gamestate;
public:
    UndecidedLogic(ENetInterface* interface,AbstractGame* game,bool host){
        this->interface = interface;
        this->game = game;
        this->host = host;
    }
    virtual void update(float deltatime){
        if(updating){
        
            
        }
        
        auto eventsuccess = [this](std::unique_ptr<PacketObject> obj){
            
            if(obj->length>=sizeof(PacketHeader)){
                
                PacketHeader* header = (PacketHeader*)obj->data;
                if(header->signature == GAMESIGNATURE && header->packettype ==kNatReserved){
                    
                }else if(header->signature == NATSIGNATURE && header->packettype == kMatched){
                    
                    MatchPacket* mp = (MatchPacket*)obj->data;
                    CustomENet remoteaddress = {0};
                    memcpy(&remoteaddress,&mp->host,sizeof(CustomENet));
                    interface->donat(&mp->host);
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
    virtual void draw(int screenWidth,int screenHeight){
        
    }
    virtual void send(uint8_t* packet, uint32_t size){
        
    }
    virtual bool needstodraw(){
        return false;
    }
    virtual bool ishost(){
        return host;
    }
    virtual void movebroadcast(uint32_t x, uint32_t y){
        
    }
    virtual std::shared_ptr<GameState> getgamestate() {
        return gamestate;
    }
};

#endif
