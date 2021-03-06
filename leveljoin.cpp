#include <leveljoin.h>
#include <stdexcept>
//
LevelJoin::LevelJoin(AbstractGame* g,std::weak_ptr<GameLogic> logic) : Level(logic){
    l = 3;
    this->g = g;
    index = 0;
    memset(hostnamebuffer,0,sizeof(hostnamebuffer));
    charindex = 0;
}
void LevelJoin::input(){
    std::string hostnamestring(hostnamebuffer);
    if(IsKeyReleased(KEY_ESCAPE)){
        g->destroylevel(0);
    }
    if(IsKeyReleased(KEY_ENTER)){
        uint64_t uhostname = 0;
        try{
            uhostname = std::stoull(hostnamebuffer,nullptr,16);
        }
        catch(std::invalid_argument& e){
        }
        if(uhostname!=0){
            std::shared_ptr<GameLogic> locked = logic.lock();
            if(locked){
                std::shared_ptr<OutOfGameLogic> ogl = std::dynamic_pointer_cast<OutOfGameLogic>(locked);
                if(ogl){
                    if(!ogl->join(uhostname)){
                    }
                }
            }
        }
    }
    else if(IsKeyReleased(KEY_BACKSPACE)){
        
        hostnamebuffer[charindex-1] = 0;
        --charindex;
        if(charindex<0){
            charindex = 0;
        }
        --offset;
        if(offset<0){
            offset = 0;
        }
        
    }
    int n = GetCharPressed();
    if(n){
        if(charindex<32){
            hostnamebuffer[charindex++] = (char)n;
        }
        ++offset;
        
    }
}
void LevelJoin::update(){
    input();
    
    
}
void LevelJoin::draw(){
    ClearBackground(RAYWHITE);
    std::vector<std::string> buffers = {"Enter hostname to join"};
    
    for(size_t i = 0; i < buffers.size();++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            DrawText(buffers.at(i).c_str(), g->getscreenwidth()/2-100 , g->getscreenheight()/2+(i*50) ,20, text);
        }
    }
    DrawText((char*)hostnamebuffer, g->getscreenwidth()/2+(-1*offset*5) , g->getscreenheight()/2+50 ,20, BLACK);
    std::shared_ptr<GameLogic> locked = logic.lock();
    if(locked->displaystatus()){
        int offset = g->getscreenwidth()/2;
        uint16_t status = locked->getstatusforgameplay();
        switch(status){
            case kMatchMakingStatusBadHostName:
                DrawText("Invalid host name",offset-100,200,20,DARKGRAY);
                break;
            case kMatchMakingStatusFailedConnection:
                DrawText("Failed to connect try again in a bit",offset-150,200,20,DARKGRAY);
                break;
            default:
                
                break;
        }
    }
}
int LevelJoin::getlevel(){
    return l;
}
void LevelJoin::drawtextforlogic(const std::vector<std::string>& buffers){
    
}
