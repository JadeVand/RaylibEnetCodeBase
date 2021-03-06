
#include <levelque.h>

LevelQue::LevelQue(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic) {
    l = 2;
    this->g = g;
    index = 0;
}
void LevelQue::input(){
    if(IsKeyReleased(KEY_ESCAPE)){
        g->destroylevel(0);
    }
}
void LevelQue::update(){
    input();
    
    
}
void LevelQue::draw(){
    ClearBackground(RAYWHITE);
    std::vector<std::string> buffers = {"In Queue"};

    for(size_t i = 0; i < buffers.size();++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            DrawText(buffers.at(i).c_str(), g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50) ,20, text);
        }
       
    }
}
int LevelQue::getlevel(){
    return l;
}
void LevelQue::drawtextforlogic(const std::vector<std::string>& buffers){
    
}

