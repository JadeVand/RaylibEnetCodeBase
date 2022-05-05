#include <levelhost.h>
LevelHost::LevelHost(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    l = 4;
    this->g = g;
    index = 0;
}
void LevelHost::input(){
    if(IsKeyReleased(KEY_ENTER)){

    }
}
void LevelHost::update(){
    input();
    
    
}
void LevelHost::draw(){
    
    
    std::shared_ptr<GameLogic> locked = logic.lock();
    
    if(locked){
        locked->draw(g->getscreenwidth(),g->getscreenheight());
        if(locked->needstodraw()){
            locked->draw(g->getscreenwidth(),g->getscreenheight());
        }else{
            char* buffers[] = {"Connecting to matchmaking server"};
            
            for(int i = 0; i < sizeof(buffers)/sizeof(void*);++i){
                Color text = { 130, 130, 130, 255 };
                if(index == i){
                    text.r = 230;
                    text.g = 41;
                    text.b = 55;
                    DrawText(buffers[i], g->getscreenwidth()/2 - 200 , g->getscreenheight()/2+(i*50) ,20, text);
                }
                
            }
        }
        
    }
}
int LevelHost::getlevel(){
    return l;
}
