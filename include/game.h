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
    NetLogic nl;
    std::weak_ptr<GameLogic> logic;
public:
    Game(int screenWidth,int screenHeight);
    ~Game();
    void update();
    void updategamelogic(float deltatime);
    void draw();
    void inputcallback(int action);
    int getscreenwidth();
    int getscreenheight();
    void destroylevel(int action);
    
    
    /*
     THese functions will change the stage to GameLevel class and will allow gamepay. If we're the host, then host logic is used, if we're the client then client logic is used.
     Two functions: creategameashost and creategameasclient
     allow the Game class to create a new logic and a new stage
     respectively
     Hostlogic : LevelGame
     ClientLogic : Level game
     */
    //undecidedlogic will call this in case we're the host
    void creategamelevelashostlogic();
    //undecidedlogic will cal this in case we're the client
    void creategamelevelasclientlogic();
    
    
    /*
     In case we've already decided on being Hostlogic or ClientLogic then we'll call creategamelevelascurrentlogic
     
     This will create a new stage but leave the logic untouched
     */
    void creategamelevelascurrentlogic();
};
#endif
