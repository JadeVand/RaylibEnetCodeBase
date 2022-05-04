#ifndef _game_h
#define _game_h
#include <levelmenu.h>
#include <levelgame.h>
#include <leveljoin.h>
#include <levelhost.h>
#include <levelque.h>
class Game : public AbstractGame{
private:
    std::shared_ptr<Level> stage;
    int screenWidth;
    int screenHeight;
    GameLogic* logic;
public:
    Game(int screenWidth,int screenHeight,GameLogic* logic);
    ~Game();
    void update();
    void draw();
    void inputcallback(int action);
    int getscreenwidth();
    int getscreenheight();
};
#endif
