#ifndef _hostlogic_h
#define _hostlogic_h
#include <outofgamelogic.h>
enum StopProcessingState{
  kProcessingStateNone = 0,
    kProcessingStateConnectionFailure = 1,
    kProcessingStateWinner = 2,
    kProcessingStateLoser = 3,
    kProcessingStateDraw = 4
};
class InGameLogic : public OutOfGameLogic{
private:
    uint64_t hostname;
    bool failedtoconnect;
    std::shared_ptr<GameState> gamestate;
    bool processing;
    StopProcessingState procstate;
public:
    InGameLogic(ENetInterface* interface,AbstractGame* game,bool host);
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
    bool needstodraw();
    void handlenetforlevel(uint8_t* data,size_t length,int result);
    std::shared_ptr<GameState> getgamestate();
    void creategamestate();
    bool processmove(uint32_t x, uint32_t y,Entity* e);
    bool processmovelocal(uint32_t x, uint32_t y);
    bool ishost();
    bool isprocessing();
    StopProcessingState getprocestate();
    
};
#endif
