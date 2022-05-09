#include <game.h>
Game::Game(int screenWidth,int screenHeight) : nl(this){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    nl.createnet();
    std::weak_ptr<OutOfGameLogic> logic = nl.makeoutofgamelogicaseither();
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
    std::weak_ptr<OutOfGameLogic> logic = nl.makeoutofgamelogicaseither();
    stage = std::make_shared<LevelMenu>(this,logic);
    nl.createnet();
}
void Game::creategamelevelashostlogic(){
    std::weak_ptr<InGameLogic> logic = nl.makeingamelogicashost();
    stage = std::make_shared<LevelGame>(this,logic);
}
void Game::creategamelevelasclientlogic(){
    std::weak_ptr<InGameLogic> logic = nl.makeingamelogicasclient();
    stage = std::make_shared<LevelGame>(this,logic);
}
void Game::creategamelevelasunknownlogic(){
    std::weak_ptr<InGameLogic> logic = nl.makeingamelogicaseither();
    stage = std::make_shared<LevelGame>(this,logic);
}
void Game::drawtextforlogic(const std::vector<std::string>& buffers){
    stage->drawtextforlogic(buffers);
}
void Game::inputcallback(int action){
    switch(action){
        case 0:{
            std::weak_ptr<OutOfGameLogic> logic = nl.makeoutofgamelogicashost();
            std::shared_ptr<OutOfGameLogic> locked = logic.lock();
            if(locked){
                if(locked->hostgame()){
                    stage = std::make_shared<LevelHost>(this,logic);
                }
            }
            
        }
            
            break;
        case 1:{
            std::weak_ptr<OutOfGameLogic> logic = nl.makeoutofgamelogicasclient();
            stage = std::make_shared<LevelJoin>(this,logic);
        }
            
            break;
        case 2:{
            std::weak_ptr<OutOfGameLogic> logic = nl.makeoutofgamelogicaseither();
            std::shared_ptr<OutOfGameLogic> locked = logic.lock();
            if(locked){
                if(locked->que()){
                    stage = std::make_shared<LevelQue>(this,logic);
                }
            }
        }
            
            break;
        case 3:{//lan player
            /*
            logic = nl.makeundecidedlogic();
            stage = std::make_shared<LevelQue>(this,logic);
             */
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

