#ifndef _hostlogic_h
#define _hostlogic_h
#include <gamelogic.h>
class HostLogic : public GameLogic{
public:
    HostLogic();
    void startlogic();
    void stoplogic();
    void update(float deltatime);
    void draw(int screenWidth,int screenHeight);
};
#endif
