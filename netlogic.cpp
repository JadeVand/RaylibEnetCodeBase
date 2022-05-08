#include <netlogic.h>
NetLogic::NetLogic(AbstractGame* game){
    logic = nullptr;
    this->game = game;
}
std::weak_ptr<InGameLogic> NetLogic::makeingamelogicashost(){
    logic = std::make_shared<InGameLogic>(&interface,game,true);
    return std::dynamic_pointer_cast<InGameLogic>(logic);
}
std::weak_ptr<InGameLogic> NetLogic::makeingamelogicasclient(){
    logic = std::make_shared<InGameLogic>(&interface,game,false);
    return std::dynamic_pointer_cast<InGameLogic>(logic);
}
std::weak_ptr<InGameLogic> NetLogic::makeingamelogicaseither(){
    /*this check should always pass so maybe do assert here?
    /*because this function can not get called unless a previous logic was established
     */
    if(logic){
        if(logic->ishost()){
            logic = std::make_shared<InGameLogic>(&interface,game,true);
        }else{
            logic = std::make_shared<InGameLogic>(&interface,game,false);
        }
    }
    return std::dynamic_pointer_cast<InGameLogic>(logic);
}

std::weak_ptr<OutOfGameLogic> NetLogic::makeoutofgamelogicashost(){
    logic = std::make_shared<OutOfGameLogic>(&interface,game,true);
    return logic;
}
std::weak_ptr<OutOfGameLogic> NetLogic::makeoutofgamelogicasclient(){
    logic = std::make_shared<OutOfGameLogic>(&interface,game,false);
    return logic;
}
std::weak_ptr<OutOfGameLogic> NetLogic::makeoutofgamelogicaseither(){
    logic = std::make_shared<OutOfGameLogic>(&interface,game,false);
    return logic;
}
void NetLogic::updatelogic(float deltatime){
    logic->update(deltatime);
}
void NetLogic::destroynet(){
    interface.destroynet();
}
void NetLogic::createnet(){
    interface.createnet();
}
