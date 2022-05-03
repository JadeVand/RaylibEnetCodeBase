#ifndef _levelque_h
#define _levelque_h

#include <level.h>
class LevelQue : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
public:
    LevelQue(AbstractGame* g);
    void input();
    void update();
    void draw();
    int getlevel();

};
#endif
