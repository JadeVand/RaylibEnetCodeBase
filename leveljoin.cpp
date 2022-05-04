#include <leveljoin.h>
LevelJoin::LevelJoin(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    l = 3;
    this->g = g;
    index = 0;
}
void LevelJoin::input(){
    if(IsKeyReleased(KEY_ENTER)){
        g->inputcallback(0);
    }
}
void LevelJoin::update(){
    input();
    
    
}
void LevelJoin::draw(){
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
int LevelJoin::getlevel(){
    return l;
}
