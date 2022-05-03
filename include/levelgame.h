#ifndef _levelgame_h
#define _levelgame_h
#include <level.h>
class LevelGame : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
    GameLogic* logic;
public:
    LevelGame(AbstractGame* g,GameLogic* logic);
    void input();
    void update();
    void draw();
    int getlevel();
};
#endif
