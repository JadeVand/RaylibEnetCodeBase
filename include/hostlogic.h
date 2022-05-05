#ifndef _hostlogic_h
#define _hostlogic_h
#include <undecidedlogic.h>
class HostLogic : public UndecidedLogic{
protected:
    uint64_t hostname;
    bool failedtoconnect;
public:
    HostLogic(ENetInterface* interface);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void host();
    void send(uint8_t* packet,uint32_t size);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
};
#endif
