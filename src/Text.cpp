#include "Game_include.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, 
        TextStyle style, std::string text, SDL_Color color, int tickTime)
    : Component(associated), text(text), style(style), fontFile(fontFile),
    fontSize(fontSize), color(color), opacity(255), timer(Timer()), tickTime(tickTime), 
    followFunction(nullptr){
    texture = nullptr;
    RemakeTexture();
}

Text::~Text(){ if (texture != nullptr) SDL_DestroyTexture(texture);}
void Text::RemakeTexture(){

    if (texture != nullptr) {
        // erro com lixo de memória
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    font = Resources::TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) return;
    SDL_Surface* surface = nullptr;
    color.a = opacity;
    if (style == TextStyle::SOLID) surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (style == TextStyle::SHADED) surface = TTF_RenderText_Shaded(font, text.c_str(), color, Colors::name["BLACK"]);
    if (style == TextStyle::BLENDED) surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) return;
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) return;
    int w, h;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0) return;
    // std::cout << "Textura criada com largura: " << w << " e altura: " << h << std::endl;
    associated.box.w = (float)w;
    associated.box.h = (float)h;

}
void Text::Update(float dt){
    if (tickTime){
        timer.Update(dt);
        if (timer.Get() > tickTime) timer.Restart();
        
        if (timer.Get() <= tickTime/2) SetOpacity((int)(256 - 2*timer.Get()*255/tickTime));
        else SetOpacity((int)(2*timer.Get()*255/tickTime - 254));
    }
    std::string new_text = "";
    if (followFunction) new_text = std::to_string(followFunction());
    if (!new_text.empty()) SetText(new_text);
}
void Text::Render(){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Rect dstRect = {(int)associated.box.x - (int)(Camera::pos.x), (int)associated.box.y - (int)(Camera::pos.y),
                        (int)(associated.box.w), (int)(associated.box.h)};
    SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};
    SDL_RenderCopyEx(renderer, texture, &clipRect, &dstRect, associated.angleDeg*180.0/Config::name["PI"], nullptr, SDL_FLIP_NONE);

}
bool Text::Is(std::string) const{ return true;}
void Text::Start(){ started = true;}
void Text::NotifyCollision(GameObject& other){}
void Text::SetText(std::string text){ this->text = text; RemakeTexture();}
void Text::SetColor(SDL_Color color){ this->color = color; RemakeTexture();}
void Text::SetStyle(TextStyle style){ this->style = style; RemakeTexture();}
void Text::SetFontFile(std::string fontFile){ this->fontFile = fontFile; RemakeTexture();}
void Text::SetFontSize(int size){ fontSize = size; RemakeTexture();}
void Text::SetOpacity(int opacity){ this->opacity = opacity; RemakeTexture();}
void Text::SetFollowFunction(IntFunct function){ this->followFunction = function;}
