#ifndef _leveljoin_h
#define _leveljoin_h

#include <level.h>
class LevelJoin : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
public:
    LevelJoin(AbstractGame* g);
    void input();
    void update();
    void draw();
    int getlevel();

};
#endif
