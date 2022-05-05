#ifndef _level_h
#define _level_h
#include <abstractgame.h>
class Level{
protected:
    std::weak_ptr<GameLogic> logic;
public:
    Level(std::weak_ptr<GameLogic> logic){
        this->logic = logic;
    }
    virtual void input() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual int getlevel() = 0;
};
#endif
