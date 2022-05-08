#ifndef _hostlogic_h
#define _hostlogic_h
#include <outofgamelogic.h>
class InGameLogic : public OutOfGameLogic{
private:
    uint64_t hostname;
    bool failedtoconnect;
    std::shared_ptr<GameState> gamestate;
public:
    InGameLogic(ENetInterface* interface,AbstractGame* game,bool host);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
    std::shared_ptr<GameState> getgamestate();
    void creategamestate();
    bool trymoveremote(const XoMovePacket& mp,Entity* e);
    void movebroadcast(uint32_t x, uint32_t y);
    bool ishost();
    
};
#endif
