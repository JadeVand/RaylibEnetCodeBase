
#include <levelgame.h>
LevelGame::LevelGame(AbstractGame* g){
    l = 1;
    this->g = g;
    index = 0;
}
void LevelGame::input(){
    if(IsKeyReleased(KEY_ENTER)){
        g->inputcallback(0);
    }
}
void LevelGame::update(){
    input();
    
    
}
void LevelGame::draw(){
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
int LevelGame::getlevel(){
    return l;
}
