
#ifndef _clientlogic_h
#define _clientlogic_h
#include <undecidedlogic.h>
class ClientLogic : public UndecidedLogic{
private:
    
public:
    ClientLogic(ENetInterface* interface,AbstractGame* game,bool host);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void send(uint8_t* packet,uint32_t size);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
    std::shared_ptr<GameState> getgamestate();
    void creategamestate();
    bool trymoveremote(const XoMovePacket& mp,Entity* e);
    void movebroadcast(uint32_t x, uint32_t y);
    bool ishost();
};
#endif
