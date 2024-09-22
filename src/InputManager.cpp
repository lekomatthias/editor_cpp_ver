#include "Game_include.h"

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
    : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0){
    std::fill(std::begin(mouseState), std::end(mouseState), false);
    std::fill(std::begin(mouseUpdate), std::end(mouseUpdate), 0);
}

InputManager::~InputManager(){}

void InputManager::Update(){
    updateCounter ++;
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) quitRequested = true;
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if (!mouseState[event.button.button]) mouseUpdate[event.button.button] = updateCounter;
            mouseState[event.button.button] = true;
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            if (mouseState[event.button.button]) mouseUpdate[event.button.button] = updateCounter;
            mouseState[event.button.button] = false;
        }
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_ESCAPE) quitRequested = true;
            else {
                if (!keyState[event.key.keysym.sym]) keyUpdate[event.key.keysym.sym] = updateCounter;
                keyState[event.key.keysym.sym] = true;
            }
        }
        if(event.type == SDL_KEYUP){
            if (keyState[event.key.keysym.sym]) keyUpdate[event.key.keysym.sym] = updateCounter;
            keyState[event.key.keysym.sym] = false;
        }
    }
}

bool InputManager::KeyPress(int key){ return (keyState[key] && keyUpdate[key]==updateCounter);}
bool InputManager::KeyRelease(int key){ return (!keyState[key] && keyUpdate[key]==updateCounter);}
bool InputManager::IsKeyDown(int key){ return keyState[key];}
bool InputManager::MousePress(int button){ return (mouseState[button] && mouseUpdate[button]==updateCounter);}
bool InputManager::MouseRelease(int button){ return (!mouseState[button] && mouseUpdate[button]==updateCounter);}
bool InputManager::IsMouseDown(int button){ return mouseState[button];}
int InputManager::GetMouseX(){ return mouseX;}
int InputManager::GetMouseY(){ return mouseY;}
bool InputManager::QuitRequested(){ return quitRequested;}
