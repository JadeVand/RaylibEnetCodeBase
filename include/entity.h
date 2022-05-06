
#ifndef _entity_h
#define _entity_h
#include <enetinterface.h>
#include <memory>
#include <vector>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
class Entity{
private:
    uint32_t xoid;
public:
    
    Entity();
    
    void setxoid(uint32_t xoid);
};
#endif
