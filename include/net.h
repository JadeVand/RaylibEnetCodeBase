#ifndef _net_h
#define _net_h
#include <abstractnet.h>

class Net : public AbstractNet{
    void open(const char* ip,const char* port);
    
};

#endif
