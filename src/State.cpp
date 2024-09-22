#include "Game_include.h"

State::State() : popRequested(false), quitRequested(false), started(false){
    std::cout << "Estado de programa criado." << std::endl;
}
State::~State(){ 
    objectArray.erase(std::remove_if(objectArray.begin(), objectArray.end(),
                [](const std::shared_ptr<GameObject>& obj) { return true;}), objectArray.end());
    objectArray.clear();
    std::cout << "Estado de programa deletado." << std::endl;
}
void State::StartArray(){ for (const auto& obj : objectArray) if (obj != nullptr) obj->Start();}
void State::UpdateArray(float dt){ for (const auto& obj : objectArray) if (obj != nullptr) obj->Update(dt);}
void State::RenderArray(){
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_RenderClear(renderer);
    for (const auto& obj : objectArray) if (obj != nullptr) obj->Render();
    SDL_RenderPresent(renderer);
}
std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> sharedPtr(go);
    objectArray.push_back(sharedPtr);
    if (started) sharedPtr->Start();
    std::weak_ptr<GameObject> weakPtr(sharedPtr);
    return weakPtr;
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
    std::weak_ptr<GameObject> weakPtr;
    for (const auto& ptr : objectArray) {
        if (ptr.get() == go) {
            weakPtr = ptr;
            break;
        }
    }
    return weakPtr;
}
bool State::PopRequested(){ return popRequested;}
bool State::QuitRequested(){ return quitRequested;}
