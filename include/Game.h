#ifndef GAME_H
#define GAME_H

class Game {
private:
    std::string title;
    int width;
    int height;
    int dt;
    int frameStart;
    SDL_Window* window;
    SDL_Renderer* renderer;
    StageState* state;

    static Game* Instance;
    State* storedState;
    std::stack<std::unique_ptr<State>> stateStack;

    Game(const std::string& title, int width, int height, int dt=33, int frameStart=0);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    void CalculateDeltaTime();

public:

    ~Game();
    static Game& GetInstance(const std::string& title = "Editor de imagens",
                            const int width = Config::name["SCREEN_WIDTH"] + 100,
                            const int height = Config::name["SCREEN_HEIGHT"]);
    void Run();
    void Push(State* state);
    void Pop();
    State& GetState();
    State& GetCurrentState();
    SDL_Renderer* GetRenderer();
    float GetDeltaTime();
    int GetWidth();
    int GetHeight();
    void FirstPlan(){ SDL_RaiseWindow(window);}
};

#endif // GAME_H
