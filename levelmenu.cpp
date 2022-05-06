#include <levelmenu.h>
LevelMenu::LevelMenu(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    index = 0;
    l = 0;
    this->g = g;
}
void LevelMenu::input(){
    if(IsKeyReleased(KEY_S)){
        index++;
        index%=3;
    }
    if(IsKeyReleased(KEY_ENTER)){
        g->inputcallback(index);
    }
}
void LevelMenu::update(){
    input();
    
    
}
void LevelMenu::draw(){
    
    std::vector<std::string> buffers = {"Host","Join","Queue", "LAN"};
    for(int i = 0; i < buffers.size();++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            
        }
        DrawText(buffers.at(i).c_str(), g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50)-50 ,20, text);
    }
}
int LevelMenu::getlevel(){
    return l;
}
void LevelMenu::drawtextforlogic(std::vector<std::string> buffers){
    
}
