#include <levelmenu.h>
LevelMenu::LevelMenu(AbstractGame* g){
    index = 0;
    l = 0;
    this->g = g;
}
void LevelMenu::input(){
    if(IsKeyReleased(KEY_S)){
        index++;
        index%=2;
    }
    if(IsKeyReleased(KEY_ENTER)){
        switch(index){
            case 0:
                g->inputcallback(0);
                break;
            case 1:
                break;
            default:
                break;
                
        }
    }
}
void LevelMenu::update(){
    input();
    
    
}
void LevelMenu::draw(){
    
    char* buffers[] = {"Game","NOP"};

    for(int i = 0; i < sizeof(buffers)/sizeof(void*);++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            
        }
        DrawText(buffers[i], g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50) ,20, text);
    }
    
    //DrawText("NOP", screenWidth/2 , screenHeight/2+50 , 20, text);
    
   // DrawRectangleLines(screenWidth/2-15,screenHeight/2+(50*index),75,20,text);
}
int LevelMenu::getlevel(){
    return l;
}
