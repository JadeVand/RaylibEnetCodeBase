#ifndef _leveljoin_h
#define _leveljoin_h

#include <level.h>
class LevelJoin : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
    GameLogic* logic;
public:
    LevelJoin(AbstractGame* g,std::weak_ptr<GameLogic> logic);
    void input();
    void update();
    void draw();
    int getlevel();

};
#endif
