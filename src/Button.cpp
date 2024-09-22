#include "Game_include.h"

Button::Button(GameObject& associated, Rect rect, SDL_Color color, std::string label)
    : Component(associated), texture(nullptr), rect(rect), color(color), label(label){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)rect.w, (int)rect.h);

    SDL_SetRenderTarget(renderer, texture);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
}

void Button::Render(){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect clipRect = {0, 0, (int)rect.w, (int)rect.h};
    SDL_Rect dstRect = {(int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), (int)(rect.w), (int)(rect.h)};
    SDL_RenderCopyEx(renderer, texture, &clipRect, &dstRect, associated.angleDeg*180.0/Config::name["PI"], nullptr, SDL_FLIP_NONE);
}
bool Button::Is(std::string type) const{ return (type == BUTTON);}
void Button::Start(){ started = true;}
void Button::NotifyCollision(GameObject& other){}
void Button::Update(float dt){}

void Button::Press(){
    if(funct){
        std::cout << "funcao " << label << " executada." << std::endl;
        funct();
    }else{
        std::cout << "botao ativado mas sem funcao." << std::endl;
    }
}