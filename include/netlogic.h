#ifndef _netlogic_h
#define _netlogic_h

#include <hostlogic.h>
#include <clientlogic.h>

class NetLogic{
private:
    std::shared_ptr<GameLogic> logic;
    ENetInterface interface;
public:
    NetLogic(){
        logic = nullptr;
    }
    std::weak_ptr<HostLogic> makehostlogic(){
        logic = std::make_shared<HostLogic>(&interface);
        return std::dynamic_pointer_cast<HostLogic>(logic);
    }
    std::weak_ptr<ClientLogic> makeclientlogic(){
        logic = std::make_shared<ClientLogic>(&interface);
        return std::dynamic_pointer_cast<ClientLogic>(logic);
    }
    std::weak_ptr<UndecidedLogic> makeundecidedlogic(){
        logic = std::make_shared<UndecidedLogic>(&interface);
        return std::dynamic_pointer_cast<UndecidedLogic>(logic);
    }
    std::weak_ptr<GameLogic> getcurrentlogic(){
        return logic;
    }
};
#endif
