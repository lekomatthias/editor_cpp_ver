#ifndef RECT_H
#define RECT_H

class Rect{
public:
    float x, y, w, h;
    Rect() : x(0), y(0), w(0), h(0){}
    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){}
    ~Rect(){}
    void SetAll(float x, float y, float w, float h){ this->x=x; this->y=y; this->w=w; this->h=h;}
    void SetPos(float x, float y){ this->x=x; this->y=y;}
    void SetPos(Vec2 pos){ x = pos.x; y = pos.y;}
    void SetSize(float w, float h){ this->w=w; this->h=h;}
    void SetSize(Vec2 pos){ w = pos.x; h = pos.y;}
    Vec2 GetCenter(){ return Vec2(x+w/2, y+h/2);}
    Vec2 GetPos(){ return Vec2(x, y);}
    Vec2 GetSize(){ return Vec2(w, h);}
    SDL_Rect GetClip(){ return {(int)this->x, (int)this->y, (int)this->w, (int)this->h};}
    bool Contains(Vec2 pos){ return ((pos.x >= x && pos.x < x+w) && (pos.y >= y && pos.y < y+h));}
    void SetCenterPos(float x, float y){ SetPos(x-w/2, y-h/2);}
    void SetCenterPos(Vec2 pos){ SetPos(pos.x-w/2, pos.y-h/2);}

};

#endif // RECT_H