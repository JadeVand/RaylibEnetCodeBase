#ifndef _levelmenu_h
#define _levelmenu_h

#include <level.h>
class LevelMenu : public Level{
private:
    int index;
    int l;
    AbstractGame* g;
    GameLogic* logic;
public:
    LevelMenu(AbstractGame* g,GameLogic* logic);
    void input();
    void update();
    void draw();
    int getlevel();

};
#endif
