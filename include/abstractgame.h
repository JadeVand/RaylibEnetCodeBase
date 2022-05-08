#ifndef _abstractgame_h
#define _abstractgame_h
#include <entity.h>
class AbstractGame{
public:
    virtual void destroylevel(int input) = 0;
    virtual void inputcallback(int action) = 0;
    virtual int getscreenwidth() = 0;
    virtual int getscreenheight() = 0;
    virtual void creategamelevelashostlogic() = 0;
    virtual void creategamelevelasclientlogic() = 0;
    virtual void creategamelevelasunknownlogic() = 0;
};
#endif
