
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
    if(IsMouseButtonPressed(0)){//left mouse click

    }
}
void LevelGame::update(){ 
    mouseposition = GetMousePosition();
    input();
 
}

void LevelGame::draw(){
#define SQUARE_SIZE 50
    int offsetx = g->getscreenwidth()/2;
    int offsety = g->getscreenheight()/2;
    for(int i = 0; i < 3; ++i){
        for(int k = 0; k < 3; ++k){
            Color c = LIGHTGRAY;
            if(mouseposition.x>k*SQUARE_SIZE+offsetx-100 && mouseposition.x<k*SQUARE_SIZE+offsetx-100+SQUARE_SIZE){
                if(mouseposition.y>i*SQUARE_SIZE+offsety-100 && mouseposition.y< i*SQUARE_SIZE+offsety-100 +SQUARE_SIZE){
                    highlightedy = i;
                    highlightedx = k;
                    c = DARKGRAY;
                }
            }
            DrawRectangleLines(k*SQUARE_SIZE+offsetx-100, i*SQUARE_SIZE+offsety-100, SQUARE_SIZE, SQUARE_SIZE, c);
        }
        
    }

}
int LevelGame::getlevel(){
    return l;
}

void LevelGame::drawtextforlogic(std::vector<std::string> buffers){
    
}
