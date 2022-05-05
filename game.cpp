#include <game.h>
Game::Game(int screenWidth,int screenHeight) : nl(this){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    logic = nl.makeundecidedlogic();
    nl.createnet();
    stage = std::make_shared<LevelMenu>(this,logic);
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
void Game::destroylevel(int action){
    nl.destroynet();
    logic = nl.makeundecidedlogic();
    stage = std::make_shared<LevelMenu>(this,logic);
    nl.createnet();
}
void Game::createhostlevel(){
    logic = nl.makehostlogic();
    stage = std::make_shared<LevelGame>(this,logic);
}
void Game::createclientlevel(){
    logic = nl.makeclientlogic();
    stage = std::make_shared<LevelGame>(this,logic);
}
void Game::inputcallback(int action){
    switch(action){
        case 0:{
            logic = nl.makehostlogic();
            std::shared_ptr<GameLogic> locked = logic.lock();
            if(locked){
                if(locked->host()){
                    stage = std::make_shared<LevelHost>(this,logic);
                }
            }
            
            
        }
            
            break;
        case 1:{
            logic = nl.makeclientlogic();
            std::shared_ptr<GameLogic> locked = logic.lock();
            if(locked){
                //locked->join(false);
            }
            stage = std::make_shared<LevelJoin>(this,logic);
        }
            
            break;
        case 2:{
            logic = nl.makeundecidedlogic();
            std::shared_ptr<GameLogic> locked = logic.lock();
            if(locked){
                if(locked->que()){
                    stage = std::make_shared<LevelQue>(this,logic);
                }
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

