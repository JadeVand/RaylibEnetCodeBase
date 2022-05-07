#ifndef _hostlogic_h
#define _hostlogic_h
#include <undecidedlogic.h>
class HostLogic : public UndecidedLogic{
private:
    uint64_t hostname;
    bool failedtoconnect;
    std::shared_ptr<GameState> gamestate;
public:
    HostLogic(ENetInterface* interface,AbstractGame* game,bool host);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void send(uint8_t* packet,uint32_t size);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
    std::shared_ptr<GameState> getgamestate();
    void creategamestate();
    bool trymove(const XoMovePacket& mp,Entity* e);
    bool ishost();
    
};
#endif
