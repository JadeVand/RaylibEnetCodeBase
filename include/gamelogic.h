
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
    virtual void update(float deltatime) = 0;
    virtual void draw(int screenWidth,int screenHeight) = 0;
};

#endif
