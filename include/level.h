#ifndef _level_h
#define _level_h
#include <abstractgame.h>
class Level{
public:
    virtual void input() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual int getlevel() = 0;
};
#endif
