#ifndef _outofgamelogic_h
#define _outofgamelogic_h
#include <gamestate.h>
enum MatchmakingStatus : uint16_t{
    kMatchMakingStatusNone = 0,
    kMatchMakingStatusHostName = 1,
    kMatchMakingStatusBadHostName = 2,
    
};
class OutOfGameLogic : public GameLogic{
protected:

    ENetInterface* interface;
    AbstractGame* game;
    bool host;
    MatchmakingStatus mms;
    uint64_t hostname ;
public:
    OutOfGameLogic(ENetInterface* interface,AbstractGame* game,bool host);
    virtual void update(float deltatime);
    virtual void draw(int screenWidth,int screenHeight);
    virtual bool ishost();
    bool que();
    bool hostgame();
    bool join(uint64_t hostname);
    uint16_t getstatusforgameplay();
    virtual uint64_t gethostname();
};

#endif
