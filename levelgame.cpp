
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
        std::shared_ptr<GameLogic> locked = logic.lock();
        if(locked){
            locked->movebroadcast(highlightedx,highlightedy);
        }
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
    
    std::shared_ptr<GameLogic> locked = logic.lock();
    if(locked){
        std::shared_ptr<UndecidedLogic> gl = std::dynamic_pointer_cast<UndecidedLogic>(locked);
        if(gl){
            std::shared_ptr<GameState> state = gl->getgamestate();
            if(state){
                XoGrid* map = state->getmap();
                for(int n = 0; n < 9 ; ++n){
                    if(map[n].occupied){
                        int xpos = map[n].x*SQUARE_SIZE+offsetx-100+25;
                        int ypos = map[n].y*SQUARE_SIZE+offsety-100+25;
                        if(map[n].xoid==1){
                            DrawText("X",xpos,ypos,20,RED);
                        }else{
                            DrawText("O",xpos,ypos,20,RED);
                        }
                    }
                }
            }
        }
    }
    /*
    if(locked){
        
    }
     */

}
int LevelGame::getlevel(){
    return l;
}

void LevelGame::drawtextforlogic(std::vector<std::string> buffers){
    
}
