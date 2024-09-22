#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public Component{
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapse;
    float frameTime;
    float msToSelfDestruct;
    Timer selfDestructCount;

public:
    Sprite(std::string file);
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, int frameCount=1, float frameTime=1, float secondsToSelfDestruct=0);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Update(float dt) override;
    void Render() override;
    void Render(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(std::string type)const override;
    void Start() override;
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frame);
    void SetFrameTime(float frameTime);
    void NotifyCollision(GameObject& other) override;
    
};

#endif // SPRITE_H
