#include <game.h>
Game::Game(int screenWidth,int screenHeight){
    logic = nl.makeundecidedlogic();
    stage = std::make_shared<LevelMenu>(this,logic);
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}
Game::~Game(){

}
void Game::updategamelogic(float deltatime){
    nl.updatelogic(deltatime);
}
void Game::update(){
    stage->update();
}
void Game::draw(){
    stage->draw();
}
void Game::inputcallback(int action){
    switch(action){
        case 0:{
            switch(stage->getlevel()){
                case 0:{
                    logic = nl.makehostlogic();
                    std::shared_ptr<GameLogic> locked = logic.lock();
                    if(locked){
                        std::shared_ptr<HostLogic> hostlock = std::dynamic_pointer_cast<HostLogic>(locked);
                        if(hostlock){
                            hostlock->host();
                        }
                    }

                    stage = std::make_shared<LevelHost>(this,logic);
                }
                    
                    break;
                case 1:
                    logic = nl.makeclientlogic();

                    stage = std::make_shared<LevelJoin>(this,logic);
                    break;
                case 2:
                    nl.makeundecidedlogic();
                    stage = std::make_shared<LevelQue>(this,logic);
                default:
                    break;
                    
            }
        }
            break;
        default:
            break;
    }
}
int Game::getscreenwidth(){
    return screenWidth;
}
int Game::getscreenheight(){
    return screenHeight;
}

