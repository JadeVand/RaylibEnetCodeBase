
#ifndef _gamelogic_h
#define _gamelogic_h
#include <abstractlevel.h>
class GameLogic{
protected:
    ENetInterface* interface;
    bool updating;
    Entity* me;
    Entity* apponent;
    std::shared_ptr<PacketObject> latestpacket;
    AbstractGame* game;
public:
    virtual void startlogic(){
        updating = true;
    }
    virtual void stoplogic(){
        updating = false;
    }
    virtual void update(float deltatime){
        /*
        auto lambda = [this](uint8_t* data,size_t length, int result){
            this->latestpacket = std::make_shared<PacketObject>(data,length);
        };
        interface->quecompletion(lambda,1);
         */
        
    }
    virtual void draw(int screenWidth,int screenHeight) = 0;
    virtual bool que(){
        return interface->dedicatedconnect(false);
    }
    virtual bool host(){
        return interface->dedicatedconnect(true);
    }
    virtual bool join(uint64_t hostname){
        return interface->dedicatedconnect(true);
    }
    virtual Entity* getself(){
        return me;
    }
    virtual Entity* getapponent(){
        return apponent;
    }
    /*
    virtual std::weak_ptr<PacketObject> getlatestpacket(){
        return latestpacket;
    }
     */
    virtual void send(uint8_t* packet,uint32_t size) = 0;//subject to change
    
    virtual bool needstodraw() = 0;

};

#endif
