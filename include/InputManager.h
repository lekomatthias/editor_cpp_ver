#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define SDLK_SPACE          SDLK_SPACE // para lembrar q é bem intuitivo msm kkkkkk
#define SDLK_CTRL           SDLK_LCTRL // left control, existe o RCTRL

class InputManager{
private:
    InputManager();
    ~InputManager();

    std::array<bool, 6> mouseState;
    std::array<int, 6> mouseUpdate;
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;

public:
    static InputManager& GetInstance();

    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();

};

#endif // INPUTMANAGER_H