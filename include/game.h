#ifndef _game_h
#define _game_h
#include <levelmenu.h>
#include <levelgame.h>
class Game : public AbstractGame{
private:
    std::shared_ptr<Level> stage;
    int screenWidth;
    int screenHeight;
public:
    Game(int screenWidth,int screenHeight);
    ~Game();
    void update();
    void draw();
    void inputcallback(int action);
    int getscreenwidth();
    int getscreenheight();
};
#endif
