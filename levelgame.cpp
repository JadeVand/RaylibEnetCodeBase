
#include <levelgame.h>
LevelGame::LevelGame(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    l = 1;
    this->g = g;
    index = 0;
}
void LevelGame::input(){
    if(IsKeyReleased(KEY_ESCAPE)){
        g->destroylevel(0);
    }
    if(IsKeyReleased(KEY_ENTER)){
      //  g->inputcallback(0);
    }
}
void LevelGame::update(){
    input();
    
    
}
void LevelGame::draw(){
    std::vector<std::string>buffers = {"Back"};

    for(int i = 0; i < buffers.size();++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            DrawText(buffers.at(i).c_str(), g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50) ,20, text);
        }
    }
}
int LevelGame::getlevel(){
    return l;
}

void LevelGame::drawtextforlogic(std::vector<std::string> buffers){
    
}
