#ifndef _levelhost_h
#define _levelhost_h

#include <level.h>
class LevelHost : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
    GameLogic* logic;
public:
    LevelHost(AbstractGame* g,GameLogic* logic);
    void input();
    void update();
    void draw();
    int getlevel();

};
#endif
