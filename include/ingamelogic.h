#ifndef _hostlogic_h
#define _hostlogic_h
#include <outofgamelogic.h>

class InGameLogic : public OutOfGameLogic{
private:
    bool failedtoconnect;
    std::shared_ptr<GameState> gamestate;
    bool processing;
public:
    InGameLogic(ENetInterface* interface,AbstractGame* game,bool host);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    void handlenetforlevel(uint8_t* data,size_t length,int result);
    std::shared_ptr<GameState> getgamestate();
    void creategamestate();
    bool processmove(uint16_t x, uint16_t y,Entity* e);
    bool processmovelocal(uint16_t x, uint16_t y);
    bool ishost();
};
#endif
