#include "Game_include.h"

Game::Game(const std::string& title, int width, int height, int dt, int frameStart)
: title(title), width(width), height(height), dt(dt), frameStart(frameStart),
    window(nullptr), renderer(nullptr), storedState(nullptr) {
    Resources::Del();

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER |
                    SDL_INIT_AUDIO | SDL_INIT_EVENTS |
                    SDL_INIT_VIDEO | SDL_INIT_EVERYTHING |
                    SDL_INIT_JOYSTICK | SDL_INIT_NOPARACHUTE |
                    SDL_INIT_HAPTIC) != 0) {
        std::cerr << "Erro no SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG)) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Erro no SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cerr << "Erro no SDL_mixer: " << Mix_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "Erro no áudio: " << Mix_GetError() << std::endl;
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    if (TTF_Init() != 0){
        std::cerr << "Erro na SDL_TTF: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Erro na janela: " << SDL_GetError() << std::endl;
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    // aqui tem algum erro ao compilar as flags
    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC |
    //                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erro no renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }
    
}

// criacao da instancia de Game, ja com os requisitos necessarios
Game& Game::GetInstance(const std::string& title, int width, const int height){
    static Game instance(title, width, height);
    return instance;
}

void Game::CalculateDeltaTime(){
    dt = (int)SDL_GetTicks() - frameStart;
    frameStart += dt;
}

float Game::GetDeltaTime(){
    CalculateDeltaTime();
    return (float)dt;
}

int Game::GetWidth(){ return width;}
int Game::GetHeight(){ return height;}
void Game::Push(State* state){ storedState = state;}
void Game::Pop(){ stateStack.pop();}
State& Game::GetState(){ return *state;}
SDL_Renderer* Game::GetRenderer(){ return renderer;}

State& Game::GetCurrentState(){ 
    if (!stateStack.empty()) return *stateStack.top().get();
    // para nao gerar erro ao requisitar sem nada na pilha
    else return *(new StageState());
}

Game::~Game(){
    if (storedState != nullptr) storedState = nullptr;
    while (!stateStack.empty()) stateStack.pop();
    Resources::Del();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::Run() {
    if (renderer == nullptr) return;
    State* initial_state = new StageState();
    Push(initial_state);
    
    do{
        Camera::Zero();
        if (storedState != nullptr){
            GetCurrentState().Pause();
            stateStack.push(std::unique_ptr<State>(storedState));
            storedState = nullptr;
            GetCurrentState().Start();
        }
        GameData::gameFinished = false;
        GameData::playerVictory = false;
        FirstPlan();
        GetCurrentState().Resume();
        if (GetCurrentState().QuitRequested()) break;
        if (GetCurrentState().PopRequested()) Pop();

    } while (!stateStack.empty());
}
