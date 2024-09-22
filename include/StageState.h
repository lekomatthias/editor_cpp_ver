#ifndef STAGESTATE_H
#define STAGESTATE_H

class StageState : public State{
private:
    InputManager* input;
    Sprite* bg;
    Img* img;
    int dt;
    SDL_Renderer* renderer;
    SDL_Event event;
    int posX;
    int posY;

    std::vector<std::shared_ptr<GameObject >> HUDArray;
    std::vector<std::shared_ptr<SDL_Surface >> surfaceArray;
    std::vector<std::shared_ptr<SDL_Surface >> redoSurfaceArray;

    void UsersCommands();
    void NewLayer(int x, int y, SDL_Color color);
    void OverrideLayer(int x, int y, SDL_Color color);
    SDL_Surface* GetTopImg();
    SDL_Surface* GetTopImgReDo();
    void AddObject(int mouseX, int mouseY);
    void CollisionUpdate();

public:
    StageState();
    ~StageState();
    bool QuitRequested();
    void LoadAssets(float dt, std::string img_file, std::string music_file) override;
    void Update() override;
    void UpdateHUD();
    void Render() override;
    void RenderHUD();
    void Run();

    void Start() override;
    void Pause() override;
    void Resume() override;

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> AddHUD(GameObject* go);
    std::weak_ptr<SDL_Surface> AddImg(SDL_Surface* surface);
    
    void BackImg();
    std::weak_ptr<SDL_Surface> AddReDoStack(SDL_Surface* surface);
    void ReDo();
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    std::weak_ptr<GameObject> GetHUDPtr(GameObject* go);
    GameObject* NewObject();

};

#endif // STAGESTATE_H
