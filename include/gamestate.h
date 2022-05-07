#ifndef _gamestate_h
#define _gamestate_h

#include <gamelogic.h>
enum XoPacketId{
  
    kWin = 1,
    kLose = 2,
    kPause = 3,
    kResume = 4,
    kReserved = 5,
    kMove = 6,
};
typedef struct SXoMovePacket{
    PacketHeader ph;
    uint32_t x;
    uint32_t y;
}XoMovePacket;
typedef struct SXoGrid{
    uint32_t x;
    uint32_t y;
    bool occupied;
    uint32_t xoid;
}XoGrid;
class GameState{
private:
    Entity me;
    Entity apponent;
    XoGrid map[9];
    Entity* turn;
    GameLogic* logic;
public:
    GameState(uint32_t myxoid, uint32_t apponentxoid);
    /*
     Processmove gets called from either network during update
     Or from level update
     We have to be able to differentiate who sent the packet
     Since it's only two players we can simplify this process
     Pretty easily
     If level update calls it, then it passes selfentityh
     if network update calls it then it passes apponententity
     */
    bool processmove(const XoMovePacket& mp,Entity* e);
    bool checkwinner(uint32_t xoid);
    Entity* getself();
    Entity* getapponent();
    void setturn(Entity* t);
};
#endif
