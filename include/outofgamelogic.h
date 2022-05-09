#ifndef _outofgamelogic_h
#define _outofgamelogic_h
#include <gamestate.h>
class OutOfGameLogic : public GameLogic{
protected:

    ENetInterface* interface;
    AbstractGame* game;
    bool host;
public:
    OutOfGameLogic(ENetInterface* interface,AbstractGame* game,bool host);
    virtual void update(float deltatime);
    virtual void draw(int screenWidth,int screenHeight);
    virtual bool ishost();
    bool que();
    bool hostgame();
    bool join(uint64_t hostname);
};

#endif
