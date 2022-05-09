#ifndef _levelgame_h
#define _levelgame_h
#include <level.h>
#include <raylib.h>
#include <raymath.h>
class LevelGame : public Level{
private:
    int l;
    int index;
    AbstractGame* g;
    Vector2 mouseposition;
    uint16_t highlightedx;
    uint16_t highlightedy;
public:
    LevelGame(AbstractGame* g,std::weak_ptr<GameLogic> logic);
    void input();
    void update();
    void draw();
    int getlevel();
    void drawtextforlogic(const std::vector<std::string>& buffers);
};
#endif
