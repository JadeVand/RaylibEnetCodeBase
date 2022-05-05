#ifndef _undecidedlogic_h
#define _undecidedlogic_h
#include <gamelogic.h>
class UndecidedLogic : public GameLogic{
public:
    UndecidedLogic(ENetInterface* interface){
        this->interface = interface;
    }
    virtual void startlogic(){
        GameLogic::startlogic();
    }
    virtual void stoplogic(){
        GameLogic::stoplogic();
    }
    virtual void update(float deltatime){
        GameLogic::update(deltatime);
    }
    virtual void draw(int screenWidth,int screenHeight){
        
    }
    virtual void que(){
        GameLogic::que();
    }
    virtual Entity* getself(){
        return GameLogic::getself();
    }
    virtual Entity* getapponent(){
        return GameLogic::getapponent();
    }
    virtual void send(uint8_t* packet, uint32_t size){
        
    }
    virtual bool needstodraw(){
        return false;
    }
};

#endif
