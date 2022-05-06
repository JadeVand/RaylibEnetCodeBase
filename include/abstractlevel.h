
#ifndef _abstractlevel_h
#define _abstractlevel_h
#include <abstractgame.h>
class AbstractLevel{
public:
    virtual void input() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual int getlevel() = 0;
};

#endif
