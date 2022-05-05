#ifndef _hostlogic_h
#define _hostlogic_h
#include <undecidedlogic.h>
class HostLogic : public UndecidedLogic{
protected:
    uint64_t hostname;
public:
    HostLogic(ENetInterface* interface);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void host();
    void send(uint8_t* packet,uint32_t size);
};
#endif
