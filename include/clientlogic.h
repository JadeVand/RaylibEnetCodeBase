
#ifndef _clientlogic_h
#define _clientlogic_h
#include <undecidedlogic.h>
class ClientLogic : public UndecidedLogic{
public:
    ClientLogic(ENetInterface* interface);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void join(uint64_t hostname);
    void send(uint8_t* packet,uint32_t size);
};
#endif
