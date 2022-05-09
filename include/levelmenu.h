#ifndef _levelmenu_h
#define _levelmenu_h

#include <level.h>
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
    void drawtextforlogic(const std::vector<std::string>& buffers);
};
#endif
