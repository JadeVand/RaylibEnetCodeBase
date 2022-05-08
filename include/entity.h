
#ifndef _entity_h
#define _entity_h
#include <enetinterface.h>
class Entity{
private:
    uint32_t xoid;
public:
    
    Entity();
    
    void setxoid(uint32_t xoid);
    uint32_t getxoid();
};
#endif
