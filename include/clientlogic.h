
#ifndef _clientlogic_h
#define _clientlogic_h
#include <gamelogic.h>
class ClientLogic : public GameLogic{
public:
    ClientLogic();
    void startlogic();
    void stoplogic();
    void update(float deltatime);
};
#endif
