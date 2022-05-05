
#ifndef _clientlogic_h
#define _clientlogic_h
#include <undecidedlogic.h>
class ClientLogic : public UndecidedLogic{
public:
    ClientLogic(ENetInterface* interface);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void send(uint8_t* packet,uint32_t size);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
};
#endif
