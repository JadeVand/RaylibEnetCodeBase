#include <game.h>
Game::Game(int screenWidth,int screenHeight,GameLogic* logic){
    stage = std::make_shared<LevelMenu>(this,logic);
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->logic = logic;
}
Game::~Game(){

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
                    stage = std::make_shared<LevelGame>(this,logic);
                    break;
                case 1:
                    stage = std::make_shared<LevelMenu>(this,logic);
                    break;
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
