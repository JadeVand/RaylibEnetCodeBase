#ifndef _netlogic_h
#define _netlogic_h
//I forgot why I even made this class LOL
//could I have not just an interface pointer in Game
//instead of using NetLogic* ?
//Like this class doesn't even really do anything I really don't get it
//but I have it and it works so it's saying

#include <ingamelogic.h>
class UnableToConnectException : public std::exception{
    const char* what(){
        return "Unable to connect to server";
    }
};
class NetLogic{
private:
    std::shared_ptr<OutOfGameLogic> logic;
    ENetInterface interface;
    AbstractGame* game;
public:
    NetLogic(AbstractGame* game);
    /*
     matchmaking server told us we're the host
     */
    std::weak_ptr<InGameLogic> makeingamelogicashost();
    
    /*
     matchmaking server told us we're the client
     */
    std::weak_ptr<InGameLogic> makeingamelogicasclient();
    
    /*
     We pressed either host or join earlier and now our logic remembers so we create appropriate game logic
     
     We call ishost from previously established logic when we
     pressed either join or host, if we are host we
     create ingamelogic as true
     
     if we aren't host we create ingamelogic as false
     */
    std::weak_ptr<InGameLogic> makeingamelogicaseither();
    /*
     This gets called when a player presses host in level menu
     */
    std::weak_ptr<OutOfGameLogic> makeoutofgamelogicashost();
    
    /*
     This gets called when a player presses join in level menu
     */
    std::weak_ptr<OutOfGameLogic> makeoutofgamelogicasclient();
    
    /*
     this gets called when a player hits queue in level menu
     */
    std::weak_ptr<OutOfGameLogic> makeoutofgamelogicaseither();
    void updatelogic(float deltatime);
    void destroynet();
    void createnet();
};
#endif
