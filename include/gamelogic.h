
#ifndef _gamelogic_h
#define _gamelogic_h
#include <entity.h>
class GameLogic{
public:
    virtual void startlogic() = 0;
    virtual void stoplogic() = 0;
    virtual void update(float deltatime) = 0;
};

#endif
