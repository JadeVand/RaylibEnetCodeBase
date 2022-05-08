#ifndef _levelque_h
#define _levelque_h

#include <level.h>
class LevelQue : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
public:
    LevelQue(AbstractGame* g,std::weak_ptr<GameLogic> logic);
    void input();
    void update();
    void draw();
    int getlevel();
    void drawtextforlogic(std::vector<std::string> buffers);
};
#endif
