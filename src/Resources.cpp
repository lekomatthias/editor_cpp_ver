#include "Game_include.h"

std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

Resources::~Resources(){
    void ClearImages();
    void ClearMusic();
    void ClearSounds();
    void ClearFonts();
}
void Resources::Del(){
    void ClearImages();
    void ClearMusic();
    void ClearSounds();
    void ClearFonts();
}

SDL_Texture* Resources::GetImage(std::string file){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    auto texture = imageTable.find(file);
    if (texture == imageTable.end()){
        SDL_Texture* newtexture = IMG_LoadTexture(renderer, file.c_str());
        if (newtexture == nullptr) return nullptr; 
        imageTable[file] = newtexture;
        return newtexture;
    }
    return texture->second;
}
void Resources::ReloadImage(const std::string file) {
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    auto texture = imageTable.find(file);
    if (texture != imageTable.end()) {
        SDL_DestroyTexture(texture->second);
    }
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, file.c_str());
    if (newTexture) {
        imageTable[file] = newTexture;
    }
}
void Resources::ClearImages(){
    for (const auto& texture : imageTable) SDL_DestroyTexture(texture.second);
    imageTable.clear();
}
Mix_Chunk* Resources::GetSound(std::string file){
    auto sound = soundTable.find(file);
    if (sound == soundTable.end()){
        Mix_Chunk* newsound = Mix_LoadWAV(file.c_str());
        if (newsound == nullptr) return nullptr; 
        soundTable[file] = newsound;
        return newsound;
    }
    return sound->second;
}
void Resources::ClearSounds(){
    for (const auto& sound : soundTable) Mix_FreeChunk(sound.second);
    soundTable.clear();
}
TTF_Font* Resources::TTF_OpenFont(const char* file, int ptsize){
    std::string key = std::string(file) + std::to_string(ptsize);
    auto font = fontTable.find(key);
    if (font == fontTable.end()){
        // este :: e para chamar a funcao SDL TTF_OpenFont, assim a funcao nao e recursiva!!!!!
        TTF_Font* newfont = ::TTF_OpenFont(file, ptsize);
        if (newfont == nullptr) return nullptr; 
        fontTable[key] = newfont;
        return newfont;
    }
    return font->second;
}
void Resources::TTF_CloseFont(TTF_Font* font){
    TTF_CloseFont(font);
}
void Resources::ClearFonts(){
    for (const auto& font : fontTable) TTF_CloseFont(font.second);
    fontTable.clear();
}
