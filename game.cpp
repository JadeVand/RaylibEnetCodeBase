#include <game.h>
Game::Game(int screenWidth,int screenHeight){
    //stage = std::make_shared<LevelMenu>(this,logic);
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}
Game::~Game(){

}
void Game::updategamelogic(float deltatime){
    
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
                case 0:
                    //logic = std::make_shared<HostLogic>();
                    //call host here?
                    //stage = std::make_shared<LevelHost>(this,logic);
                    break;
                case 1:
                    //logic = std::make_shared<HostLogic>();
                    //stage = std::make_shared<LevelJoin>(this,logic);
                    break;
                case 2:
                    //stage = std::make_shared<LevelQue>(this,logic);
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

