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
     The reason this function exists is because when a player ques up to the matchmaking server to host, their logic is assigned to host and when they que up to matchmaking server as client, their logic is assigned to client. But once the request is made, that information is lost from the game object. Then when the server responds with kPeerId it doesn't tell us if we were the host or the client, however the NetLogic object remembers if we're the host or the client because we haven't changed it after craeting the object
     
     
     In essence when this function is called, it will call NetLogic::ishost() and
    if we set to host  before making a request to the matchmaking server then creategamelevelashostlogic is called
     if we set to non host before making a request to the matchmaking server then creategalevelasclientlogic is called
     
     if
     */
    void creategamelevelasunknownlogic();
    
    
    /*
     *This can be called from game logic to render text
     */
    void drawtextforlogic(const std::vector<std::string>& buffers) ;
};
#endif
