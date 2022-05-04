#ifndef _abstractgame_h
#define _abstractgame_h
#include <netlogic.h>
class AbstractGame{
public:
    virtual void inputcallback(int input) = 0;
    virtual int getscreenwidth() = 0;
    virtual int getscreenheight() = 0;
};
#endif
