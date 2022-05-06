#ifndef _levelmenu_h
#define _levelmenu_h

#include <level.h>
#include <raylib.h>
#include <raymath.h>
class LevelMenu : public Level{
private:
    int index;
    int l;
    AbstractGame* g;
public:
    LevelMenu(AbstractGame* g,std::weak_ptr<GameLogic> logic);
    void input();
    void update();
    void draw();
    int getlevel();
    void drawtextforlogic(std::vector<std::string> buffers);
};
#endif
