#include <levelhost.h>
LevelHost::LevelHost(AbstractGame* g,GameLogic* logic){
    l = 4;
    this->g = g;
    index = 0;
    this->logic = logic;
}
void LevelHost::input(){
    if(IsKeyReleased(KEY_ENTER)){
        g->inputcallback(0);
    }
}
void LevelHost::update(){
    input();
    
    
}
void LevelHost::draw(){
    char* buffers[] = {"Back"};

    for(int i = 0; i < sizeof(buffers)/sizeof(void*);++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            
        }
       //DrawText(buffers[i], g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50) ,20, text);
        Vector2 center = (Vector2){100,100};
        DrawPolyLines(center, 6, 10, 0, text);
    }
}
int LevelHost::getlevel(){
    return l;
}
