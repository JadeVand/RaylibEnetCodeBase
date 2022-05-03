#ifndef _abstractgame_h
#define _abstractgame_h
#include "raylib.h"
#include "raymath.h"
#include <memory>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
class AbstractGame{
public:
    virtual void inputcallback(int input) = 0;
    virtual int getscreenwidth() = 0;
    virtual int getscreenheight() = 0;
};
#endif
