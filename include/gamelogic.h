
#ifndef _gamelogic_h
#define _gamelogic_h
#include <entity.h>
class GameLogic{
protected:
    ENetInterface interface;
    bool updating;
public:
    virtual void startlogic(){
        updating = true;
    }
    virtual void stoplogic(){
        updating = false;
    }
    virtual void update(float deltatime){
        auto lambda = [this](uint8_t* data,size_t length, int result){
            
        };
        interface.quecompletion(lambda,0);
        
    }
    virtual void draw(int screenWidth,int screenHeight) = 0;
    virtual void que(){
        interface.dedicatedconnect(false);
    }
};

#endif
