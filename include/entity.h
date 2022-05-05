
#ifndef _entity_h
#define _entity_h
#include <raylib.h>
#include <raymath.h>
#include <enetinterface.h>
#include <memory>
#include <vector>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
class Entity{
private:
    int choice;
public:
    Entity();
    void setchoice(int choice);
    int getchoice();
};
#endif
