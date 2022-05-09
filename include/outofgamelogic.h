#ifndef _outofgamelogic_h
#define _outofgamelogic_h
#include <gamestate.h>
enum MatchmakingStatus : uint16_t{
    kMatchMakingStatusFailedConnection = 3,
    kMatchMakingStatusBadHostName = 2,
    kMatchMakingStatusHostName = 1,
    kMatchMakingStatusNone = 0,
    kMatchMakingStateWinner = 5,
    kMatchMakingStatePause = 4,
    kMatchMakingStateLoser = 6,
    kMatchMakingStateDraw = 7,
};

class OutOfGameLogic : public GameLogic{
protected:

    ENetInterface* interface;
    AbstractGame* game;
    bool host;
    MatchmakingStatus mms;
    uint64_t hostname ;
    
    uint64_t displaytickforstatus ;
    uint64_t totaldisplaytime;
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
    virtual bool displaystatus();
};

#endif
