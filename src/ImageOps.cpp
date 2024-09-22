#include "Game_include.h"

void StageState::NewLayer(int x, int y, SDL_Color color){

    img->SetPixel(x, y, color);
    SDL_Surface* newSurface = img->GetSurfaceCopy();
    AddImg(newSurface);
    // limpa a pilha redo para que ela nao volte a uma imagem errada
    redoSurfaceArray.clear();
    img->SaveImage();
    bg->Open(Config::img["CACHE"]);
}

void StageState::OverrideLayer(int x, int y, SDL_Color color){
    if (x == posX && y == posY) return;

    // codigo para fazer uma linha entre o ponto anterior e o novo
    int dx = x - posX;
    int dy = y - posY;
    int aux = 1;

    // linha horizontal
    if (dy == 0){
        if (dx > 0){
            for (int i=posX+1; i < x; ++i){
                img->SetPixel(i, y, color);
            }
        }else{
            for (int i=posX-1; i > x; --i){
                img->SetPixel(i, y, color);
            }
        }
    }
    // linha vertical
    else if (dx == 0){
        if (dy > 0){
            for (int i=posY+1; i < y; ++i){
                img->SetPixel(x, i, color);
            }
        }else{
            for (int i=posY-1; i > y; --i){
                img->SetPixel(x, i, color);
            }
        }
    // primeiro e quarto quadrante
    }else if (dx > 0){
        float a;
        // derivada <= 1
        if (dx >= abs(dy)){
            a = (float)dy/(float)dx;
            for (int i=posX+1; i < x; ++i){
                img->SetPixel(i, (int)(a*aux + posY), color);
                ++aux;  
            }
        }
        // derivada > 1
        else if (abs(dy) > dx && dy < 0){
            a = (float)dx/(float)dy;
            for (int i=y+1; i < posY; ++i){
                img->SetPixel((int)(a*aux + x), i, color);
                ++aux;
            }
        }
        else{
            a = (float)dx/(float)dy;
            for (int i=posY+1; i < y; ++i){
                img->SetPixel((int)(a*aux + posX), i, color);
                ++aux;
            }
        }
    }
    // segundo e terceiro quadrante
    else{
        float a;
        // derivada <= 1
        if ((dx <= dy && dy < 0) || (abs(dx) >= dy && dy > 0)){
            a = (float)dy/(float)dx;
            for (int i=posX-1; i > x; --i){
                img->SetPixel(i, (int)(-a*aux + posY), color);
                ++aux;
            }
        // derivada > 1
        }else if (abs(dx) < dy && dy > 0){
            a = (float)dx/(float)dy;
            for (int i=posY+1; i < y; ++i){
                img->SetPixel((int)(a*aux + posX), i, color);
                ++aux;
            }
        }else{
            a = (float)dx/(float)dy;
            for (int i=posY-1; i > y; --i){
                img->SetPixel((int)(-a*aux + posX), i, color);
                ++aux;
            }
        }
    }

    img->SetPixel(x, y, color);
    std::shared_ptr<SDL_Surface> newSurface(img->GetSurfaceCopy(), SDL_FreeSurface);
    surfaceArray.back() = newSurface;
    img->SaveImage();
    bg->Open(Config::img["CACHE"]);
}
