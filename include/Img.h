#ifndef IMG_H
#define IMG_H

class Img{
private:
    std::string path;
    SDL_Surface* surface;
    int x;
    int y;
    int z;
public:
    ~Img();
    void SetPixel(int x, int y, SDL_Color color);
    void CreateSurface();
    void LoadSurface(SDL_Texture* texture);
    void CreateImage();
    void SaveImage();
    void LoadImage();
    void OpenImage();
    void SetPath(std::string path){ this->path = path;}
    void SetSurface(SDL_Surface* surface = nullptr);
    void SetSize(int x, int y){ this->x = x; this->y = y;}
    SDL_Surface* CombineSurfaces(SDL_Surface* baseSurface, SDL_Surface* topSurface);
    SDL_Surface* ImgSumSurface(const std::vector<std::shared_ptr<SDL_Surface>>& surfaceArray);
    SDL_Surface* GetSurfaceCopy();
};

#endif // IMG_H
