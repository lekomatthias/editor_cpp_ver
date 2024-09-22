#include "Game_include.h"

Sprite::Sprite(std::string file)
    : texture(nullptr), width(0), height(0), clipRect({0, 0, 0, 0}), scale(Vec2(1, 1)), 
    frameCount(1), currentFrame(0), timeElapse(0), frameTime(1), msToSelfDestruct(0) {
    Open(file);
}
Sprite::Sprite(GameObject& associated)
    : Component(associated), texture(nullptr), width(0), height(0), clipRect({0, 0, 0, 0}),
    scale(Vec2(1, 1)), frameCount(1), currentFrame(0), timeElapse(0), frameTime(1), msToSelfDestruct(0) {
}
Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct)
    : Component(associated), texture(nullptr), width(0), height(0), clipRect({0, 0, 0, 0}), 
    scale(Vec2(1, 1)), frameCount(frameCount), currentFrame(0), timeElapse(0), frameTime(frameTime*1000), 
    msToSelfDestruct(secondsToSelfDestruct*1000), selfDestructCount(Timer()) {
    Open(file);
}
Sprite::~Sprite(){}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
    if (texture == nullptr) return;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    width = width/frameCount;
    SetClip(0, 0, width, height);
    if (&associated != nullptr){
        associated.box.w = width;
        associated.box.h = height;
    }
}
void Sprite::SetClip(int x, int y, int w, int h){clipRect = {x, y, w, h};}
void Sprite::Update(float dt){
    timeElapse += dt;
    if (timeElapse >= frameTime){
        timeElapse = 0;
        currentFrame += 1;
        if (currentFrame >= frameCount) currentFrame = 0;
        SetFrame(currentFrame);
    }
    if (msToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > msToSelfDestruct) associated.RequestDelete();
    }
}
void Sprite::Render(){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect dstRect = {(int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), (int)(width*scale.x), (int)(height*scale.y)};
    SDL_RenderCopyEx(renderer, texture, &clipRect, &dstRect, associated.angleDeg*180.0/Config::name["PI"], nullptr, SDL_FLIP_NONE);
}
void Sprite::Render(int x, int y, int w, int h){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect dstRect = {x, y, w, h};
    SDL_RenderCopyEx(renderer, texture, &clipRect, &dstRect, associated.angleDeg*180.0/Config::name["PI"], nullptr, SDL_FLIP_NONE);
}
void Sprite::SetScale(float scaleX, float scaleY){
    scale = Vec2(scaleX, scaleY);
    associated.box.SetSize(scaleX*width, scaleY*height);
    Vec2 cPos = associated.box.GetPos();
    // a tal da matematica:
    // posicao nova = posicao antiga - tamanho original*(1-escala/2)
    // ou seja: eu passo metade do tamanho novo para tras :3
    associated.box.SetPos(cPos.x-width*(1-(1-scaleX/2)), cPos.y-height*(1-(1-scaleY/2)));
}
Vec2 Sprite::GetScale(){ return scale;}
int Sprite::GetWidth(){ return width*scale.x;}
int Sprite::GetHeight(){ return height*scale.y;}
bool Sprite::IsOpen(){ return texture != nullptr;}
bool Sprite::Is(std::string type) const{ return (type == SPRITE);}
void Sprite::Start(){ started = true;}
void Sprite::SetFrame(int frame){ SetClip(width*currentFrame, 0, width, height);}
void Sprite::SetFrameCount(int frameCount){ this->frameCount = frameCount;}
void Sprite::SetFrameTime(float frameTime){ this->frameTime = frameTime;}
void Sprite::NotifyCollision(GameObject& other){}
