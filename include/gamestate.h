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
    kRejection = 7,
};
typedef struct SXoMovePacket{
    PacketHeader ph;
    uint16_t x;
    uint16_t y;
}XoMovePacket;
typedef struct SXoGrid{
    uint16_t x;
    uint16_t y;
    bool occupied;
    uint32_t xoid;
}XoGrid;
typedef struct SRejectMovePacket{
    PacketHeader ph;
    uint16_t x;
    uint16_t y;
    uint64_t xoid;
}RejectionMovePacket;

class GameState{
private:
    Entity me;
    Entity apponent;
    XoGrid map[3][3];
    Entity* turn;
    GameLogic* logic;
    Entity* winner;
public:
    GameState(GameLogic* logic,uint32_t myxoid, uint32_t apponentxoid);
    /*
     Processmove gets called from either network during update
     Or from level update
     We have to be able to differentiate who sent the packet
     Since it's only two players we can simplify this process
     Pretty easily
     If level update calls it, then it passes selfentityh
     if network update calls it then it passes apponententity
     */
    bool processmove(uint16_t x, uint16_t y,Entity* e);
    Entity* getself();
    Entity* getapponent();
    void setturn(Entity* t);
    /*
    XoGridMap2D getmap();
     */
    bool isxyvalid(uint16_t x, uint16_t y);
    void rejectmove(uint16_t x, uint16_t y, uint32_t xoid);
    uint32_t getidforxy(uint16_t x,uint16_t y);
    bool isoccupied(uint16_t x, uint16_t y);
    void swapturn();
    
    bool isthereawinner();
    Entity* getwinner();
    bool isgameover();
};
#endif
