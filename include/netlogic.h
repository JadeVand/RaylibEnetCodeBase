#ifndef _netlogic_h
#define _netlogic_h
//I forgot why I even made this class LOL
//could I have not just an interface pointer in Game
//instead of using NetLogic* ?
//Like this class doesn't even really do anything I really don't get it
//but I have it and it works so it's saying

#include <hostlogic.h>
#include <clientlogic.h>
class UnableToConnectException : public std::exception{
    const char* what(){
        return "Unable to connect to server";
    }
};
class NetLogic{
private:
    std::shared_ptr<GameLogic> logic;
    ENetInterface interface;
    AbstractGame* game;
public:
    NetLogic(AbstractGame* game){
        logic = nullptr;
        this->game = game;
    }
    std::weak_ptr<HostLogic> makehostlogic(){
        logic = std::make_shared<HostLogic>(&interface,game,true);
        return std::dynamic_pointer_cast<HostLogic>(logic);
    }
    std::weak_ptr<ClientLogic> makeclientlogic(){
        logic = std::make_shared<ClientLogic>(&interface,game,false);
        return std::dynamic_pointer_cast<ClientLogic>(logic);
    }
    std::weak_ptr<UndecidedLogic> makeundecidedlogic(){
        logic = std::make_shared<UndecidedLogic>(&interface,game,false);
        return std::dynamic_pointer_cast<UndecidedLogic>(logic);
    }
    std::weak_ptr<GameLogic> getcurrentlogic(){
        return logic;
    }
    void updatelogic(float deltatime){
        logic->update(deltatime);
    }
    void destroynet(){
        interface.destroynet();
    }
    void createnet(){
        interface.createnet();
    }
};
#endif
