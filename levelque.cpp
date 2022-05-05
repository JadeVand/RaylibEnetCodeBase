
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
    
    std::shared_ptr<GameLogic> locked = logic.lock();
    if(locked){
        if(locked->needstodraw()){
            locked->draw(g->getscreenwidth(),g->getscreenheight());
        }else{
            char* buffers[] = {"In Que"};

            for(int i = 0; i < sizeof(buffers)/sizeof(void*);++i){
                Color text = { 130, 130, 130, 255 };
                if(index == i){
                    text.r = 230;
                    text.g = 41;
                    text.b = 55;
                    DrawText(buffers[i], g->getscreenwidth()/2 , g->getscreenheight()/2+(i*50) ,20, text);
                }
               
            }
        }
    }
    
}
int LevelQue::getlevel(){
    return l;
}
