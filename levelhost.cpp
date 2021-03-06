#include <levelhost.h>
LevelHost::LevelHost(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    l = 4;
    this->g = g;
    index = 0;
}
void LevelHost::input(){
    if(IsKeyReleased(KEY_ESCAPE)){
        g->destroylevel(0);
    }
}
void LevelHost::update(){
    input();
    
    
}
void LevelHost::draw(){
    ClearBackground(RAYWHITE);
    std::shared_ptr<GameLogic> gl = logic.lock();
    uint16_t status = gl->getstatusforgameplay();
    if(status == kMatchMakingStatusHostName){
        uint64_t hostname = gl->gethostname();
        std::string strhostname = std::to_string(hostname);
        DrawText(TextFormat("Hostname: %p",hostname),g->getscreenwidth()/2-100,g->getscreenheight()/2,20,RED);
    }else if(status == kMatchMakingStatusNone){
        std::vector<std::string> buffers = {"Waiting for hostname"};
        for(size_t i = 0; i < buffers.size();++i){
            Color text = { 130, 130, 130, 255 };
            if(index == i){
                text.r = 230;
                text.g = 41;
                text.b = 55;
                DrawText(buffers.at(i).c_str(), g->getscreenwidth()/2 - 100 , g->getscreenheight()/2+(i*50) ,20, text);
            }
            
        }
    }
    
}
int LevelHost::getlevel(){
    return l;
}
void LevelHost::drawtextforlogic(const std::vector<std::string>& buffers){
    
}
