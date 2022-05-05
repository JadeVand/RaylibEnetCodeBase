#include <leveljoin.h>
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
            printf("%p\n",uhostname);
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
    char* buffers[] = {"Enter hostname to join"};

    for(int i = 0; i < sizeof(buffers)/sizeof(void*);++i){
        Color text = { 130, 130, 130, 255 };
        if(index == i){
            text.r = 230;
            text.g = 41;
            text.b = 55;
            DrawText(buffers[i], g->getscreenwidth()/2-100 , g->getscreenheight()/2+(i*50) ,20, text);
        }
    }
    DrawText((char*)hostnamebuffer, g->getscreenwidth()/2+(-1*offset*5) , g->getscreenheight()/2+50 ,20, BLACK);
}
int LevelJoin::getlevel(){
    return l;
}
