#ifndef RESOURCES_H
#define RESOURCES_H

class Resources{
private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    static std::unordered_map<std::string, TTF_Font*> fontTable;

public:
    ~Resources();
    static void Del();
    static SDL_Texture* GetImage(std::string file);
    static void ReloadImage(std::string file);
    static void ClearImages();
    static Mix_Music* GetMusic(std::string file);
    static void ClearMusic();
    static Mix_Chunk* GetSound(std::string file);
    static void ClearSounds();
    static TTF_Font* TTF_OpenFont(const char* file, int ptsize);
    static void TTF_CloseFont(TTF_Font* font);
    static void ClearFonts();

};

#endif // RESOURCES_H