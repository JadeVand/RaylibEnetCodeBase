#ifndef _abstractnet_h
#define _abstractnet_h
#include <memory>
class NetBuffer{
public:
    char* data;
    size_t length;
};
class AbstractNet{
public:
    virtual void open(const char* ip,const char* port) = 0;

};
#endif
