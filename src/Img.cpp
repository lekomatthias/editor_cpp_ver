#include "Game_include.h"

Img::~Img() {
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
    }
}
void Img::SetPixel(int x, int y, SDL_Color color){
    Uint32* pixels = (Uint32*)surface->pixels;
    Uint32 mappedColor = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
    pixels[y * surface->w + x] = mappedColor;
}

void Img::CreateSurface(){
    surface = SDL_CreateRGBSurface(0, x, y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_Color color = Colors::name["WHITE"];
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r, color.g, color.b));
}

void Img::LoadSurface(SDL_Texture* texture){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);
    surface = SDL_CreateRGBSurface(0, x, y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
}

void Img::CreateImage(){
    CreateSurface();
    SaveImage();
}

void Img::SaveImage(){
    IMG_SavePNG(surface, path.c_str());
    Resources::ReloadImage(path);
}

void Img::LoadImage(){
    LoadSurface(Resources::GetImage(path));
}
void Img::OpenImage(){
    surface = IMG_Load(path.c_str());
}
void Img::SetSurface(SDL_Surface* surface) {
    SDL_Surface* copy = SDL_CreateRGBSurface(0, surface->w, surface->h,
                                             surface->format->BitsPerPixel,
                                             surface->format->Rmask, surface->format->Gmask, 
                                             surface->format->Bmask, surface->format->Amask);

    if (SDL_BlitSurface(surface, nullptr, copy, nullptr) < 0) {
        SDL_FreeSurface(copy);
        return;
    }
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
    }
    this->surface = copy;
}

// Função que combina duas superfícies
SDL_Surface* Img::CombineSurfaces(SDL_Surface* baseSurface, SDL_Surface* topSurface){
    if (baseSurface == nullptr || topSurface == nullptr) return nullptr;
    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, baseSurface->w, baseSurface->h, 32,
                                                   0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_SetSurfaceBlendMode(topSurface, SDL_BLENDMODE_BLEND);
    SDL_BlitSurface(baseSurface, nullptr, newSurface, nullptr);
    SDL_BlitSurface(topSurface, nullptr, newSurface, nullptr);

    return newSurface;
}
SDL_Surface* Img::ImgSumSurface(const std::vector<std::shared_ptr<SDL_Surface>>& surfaceArray){
    SDL_Surface* resultSurface = SDL_CreateRGBSurface(0, Config::name["SCREEN_WIDTH"], Config::name["SCREEN_HEIGHT"], 32,
                                                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(resultSurface, nullptr, SDL_MapRGBA(resultSurface->format, 0, 0, 0, 0));
    if (!surfaceArray.empty()){
        for (const auto& surface : surfaceArray) {
            if (surface == nullptr) continue;
            SDL_Surface* tempSurface = CombineSurfaces(resultSurface, surface.get());
            if (tempSurface != resultSurface) SDL_FreeSurface(resultSurface);
            resultSurface = tempSurface;
        }
    }
    SDL_Surface*  tempSurface = CombineSurfaces(surface, resultSurface);
    resultSurface = tempSurface;

    return resultSurface;
}
SDL_Surface* Img::GetSurfaceCopy(){
    SDL_Surface* copy = SDL_CreateRGBSurface(0, surface->w, surface->h,surface->format->BitsPerPixel,
            surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    if (SDL_BlitSurface(surface, nullptr, copy, nullptr) < 0){
        SDL_FreeSurface(copy);
        return nullptr;
    }
    return copy;
}
