#ifndef _hostlogic_h
#define _hostlogic_h
#include <gamelogic.h>
class HostLogic : public GameLogic{
public:
    HostLogic();
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void host();
    void send(uint8_t* packet,uint32_t size);
};
#endif
