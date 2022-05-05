#ifndef _abstractgame_h
#define _abstractgame_h
#include <netlogic.h>
class AbstractGame{
public:
    virtual void destroylevel(int input) = 0;
    virtual void inputcallback(int action) = 0;
    virtual int getscreenwidth() = 0;
    virtual int getscreenheight() = 0;
    virtual void createhostlevel() = 0;
    virtual void createclientlevel() = 0;
};
#endif
