#ifndef _netlogic_h
#define _netlogic_h

#include <hostlogic.h>
#include <clientlogic.h>

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
        logic = std::make_shared<HostLogic>(&interface,game);
        return std::dynamic_pointer_cast<HostLogic>(logic);
    }
    std::weak_ptr<ClientLogic> makeclientlogic(){
        logic = std::make_shared<ClientLogic>(&interface,game);
        return std::dynamic_pointer_cast<ClientLogic>(logic);
    }
    std::weak_ptr<UndecidedLogic> makeundecidedlogic(){
        logic = std::make_shared<UndecidedLogic>(&interface,game);
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
