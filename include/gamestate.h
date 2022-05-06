#ifndef _gamestate_h
#define _gamestate_h
#include <abstractlevel.h>
enum XoPacketId{
  kReserved = 5,
    kWin = 1,
    kLose = 2,
    kPause = 3,
    kResume = 4,
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
protected:
    XoGrid map[9];
public:
    GameState();
    bool processmove(const XoMovePacket& mp);
    bool checkwinner(uint32_t xoid);
};
#endif
