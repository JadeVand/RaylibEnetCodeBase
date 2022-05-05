#ifndef _undecidedlogic_h
#define _undecidedlogic_h
#include <gamelogic.h>
class UndecidedLogic : public GameLogic{
private:
    
public:
    UndecidedLogic(ENetInterface* interface){
        this->interface = interface;
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
                    if(mp->ishost){
                    }else{
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
};

#endif
