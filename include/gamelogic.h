
#ifndef _gamelogic_h
#define _gamelogic_h
#include <abstractlevel.h>
class GameLogic{
protected:
public:
    virtual void update(float deltatime){
        /*
        auto lambda = [this](uint8_t* data,size_t length, int result){
            this->latestpacket = std::make_shared<PacketObject>(data,length);
        };
        interface->quecompletion(lambda,1);
         */
        
    }
    virtual void draw(int screenWidth,int screenHeight) = 0;

    /*
    virtual std::weak_ptr<PacketObject> getlatestpacket(){
        return latestpacket;
    }
     */

    
    virtual bool ishost() = 0;
    
    virtual uint16_t getstatusforgameplay() = 0;

    virtual uint64_t gethostname() = 0;
    
    virtual bool displaystatus() = 0;
};

#endif
