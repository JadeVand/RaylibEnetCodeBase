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
    std::shared_ptr<GameLogic> logic;
public:
    Game(int screenWidth,int screenHeight);
    ~Game();
    void update();
    void updategamelogic(float deltatime);
    void draw();
    void inputcallback(int action);
    int getscreenwidth();
    int getscreenheight();
};
#endif
