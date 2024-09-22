#include "Game_include.h"

StageState::StageState()
    : State(),dt(0), renderer(Game::GetInstance().GetRenderer()){
    input = &InputManager::GetInstance();
    
    // adiciona a base do jogo como o background
    GameObject* title = new GameObject();
    AddObject(title);
    bg = new Sprite(*title);
    title->AddComponent(bg);
    Game::GetInstance().FirstPlan();

}

StageState::~StageState(){ 
    objectArray.clear();
    HUDArray.clear();
    surfaceArray.clear();
    redoSurfaceArray.clear();
}

bool StageState::QuitRequested(){ return quitRequested;}

void StageState::AddObject(int mouseX, int mouseY) {
    GameObject* newObject = new GameObject();
    AddObject(newObject);
    newObject->box.x = mouseX;
    newObject->box.y = mouseY;

}

std::weak_ptr<GameObject> StageState::AddObject(GameObject* go){
    std::shared_ptr<GameObject> sharedPtr(go);
    objectArray.push_back(sharedPtr);
    if (started) sharedPtr->Start();
    std::weak_ptr<GameObject> weakPtr(sharedPtr);
    std::cout << "objetos na fila: " << objectArray.size() << std::endl;
    return weakPtr;
}

std::weak_ptr<GameObject> StageState::AddHUD(GameObject* go){
    std::shared_ptr<GameObject> sharedPtr(go);
    HUDArray.push_back(sharedPtr);
    if (started) sharedPtr->Start();
    std::weak_ptr<GameObject> weakPtr(sharedPtr);
    std::cout << "obj HUD na fila: " << HUDArray.size() << std::endl;
    return weakPtr;
}

std::weak_ptr<SDL_Surface> StageState::AddImg(SDL_Surface* surface){
    std::shared_ptr<SDL_Surface> sharedPtr(surface, SDL_FreeSurface);
    surfaceArray.push_back(sharedPtr);
    std::weak_ptr<SDL_Surface> weakPtr(sharedPtr);
    return weakPtr;
}

std::weak_ptr<SDL_Surface> StageState::AddReDoStack(SDL_Surface* surface){
    std::shared_ptr<SDL_Surface> sharedPtr(surface, SDL_FreeSurface);
    redoSurfaceArray.push_back(sharedPtr);
    std::weak_ptr<SDL_Surface> weakPtr(sharedPtr);
    return weakPtr;
}

SDL_Surface* StageState::GetTopImg(){
    SDL_Surface* surface = surfaceArray.back().get();
    SDL_Surface* copy = SDL_CreateRGBSurface(0, surface->w, surface->h,surface->format->BitsPerPixel,
        surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    if (SDL_BlitSurface(surface, nullptr, copy, nullptr) < 0){
        SDL_FreeSurface(copy);
        return nullptr;
    }
    return copy;
}

SDL_Surface* StageState::GetTopImgReDo(){
    SDL_Surface* surface = redoSurfaceArray.back().get();
    SDL_Surface* copy = SDL_CreateRGBSurface(0, surface->w, surface->h,surface->format->BitsPerPixel,
        surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    if (SDL_BlitSurface(surface, nullptr, copy, nullptr) < 0){
        SDL_FreeSurface(copy);
        return nullptr;
    }
    return copy;
}

void StageState::BackImg(){
    if (!surfaceArray.empty()){
        SDL_Surface* surface = GetTopImg();
        AddReDoStack(surface);
        surfaceArray.pop_back();
        img->SetSurface(GetTopImg());
        img->SaveImage();
        bg->Open(Config::img["CACHE"]);
    }
}

void StageState::ReDo(){
    if (!redoSurfaceArray.empty()){
        SDL_Surface* newSurface = GetTopImgReDo();
        redoSurfaceArray.pop_back();
        AddImg(newSurface);
        img->SetSurface(newSurface);
        img->SaveImage();
        bg->Open(Config::img["CACHE"]);
    }
}

std::weak_ptr<GameObject> StageState::GetObjectPtr(GameObject* go){
    std::weak_ptr<GameObject> weakPtr;
    for (const auto& ptr : objectArray){
        if (ptr.get() == go){
            weakPtr = ptr;
            break;
        }
    }
    return weakPtr;
}

std::weak_ptr<GameObject> StageState::GetHUDPtr(GameObject* go){
    std::weak_ptr<GameObject> weakPtr;
    for (const auto& ptr : HUDArray){
        if (ptr.get() == go) {
            weakPtr = ptr;
            break;
        }
    }
    return weakPtr;
}

GameObject* StageState::NewObject(){
    GameObject* newObject = new GameObject();
    AddObject(newObject);
    return newObject;
}

void StageState::LoadAssets(float dt, std::string img_file, std::string music_file){
    bg->Open(img_file);
}

void StageState::Update(){
    input->Update();
    UsersCommands();
    Camera::Update(dt);
    UpdateHUD();
    CollisionUpdate();

    // remove objetos que retornam true para IsDeath
    auto it = std::remove_if(objectArray.begin(), objectArray.end(), 
                [](const std::shared_ptr<GameObject>& obj) { return obj->IsDeath(); });
    for (auto iter = it; iter != objectArray.end(); ++iter) { std::cout << "obj removido" << std::endl;}
    objectArray.erase(it, objectArray.end());
}

void StageState::UpdateHUD(){
    for (const auto& obj : HUDArray){
        if (obj != nullptr) obj->Update(dt);
    }
    // remove objetos que retornam true para IsDeath
    auto it = std::remove_if(HUDArray.begin(), HUDArray.end(), 
                [](const std::shared_ptr<GameObject>& obj) { return obj->IsDeath(); });
    for (auto iter = it; iter != HUDArray.end(); ++iter) { std::cout << "obj HUD removido" << std::endl;}
    HUDArray.erase(it, HUDArray.end());
}

void StageState::CollisionUpdate(){
    // loop duplo pra verificar o obj atual com todos os seguintes
    for(int i = 0; i < (int)objectArray.size()-1; ++i){
        for(int j = i+1; j < (int)objectArray.size(); ++j){
            // verifica se os dois tem component collider
            if(objectArray[i]->GetComponent(COLLIDER) != nullptr && objectArray[j]->GetComponent(COLLIDER) != nullptr){
                // verifica se ha colisao
                if (Collider::IsColliding(objectArray[i]->box, objectArray[j]->box, 
                                        objectArray[i]->angleDeg, objectArray[j]->angleDeg)){
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }
        }
    }
}

void StageState::Render(){
    SDL_RenderClear(renderer);
    for (const auto& obj : objectArray){
        if (obj != nullptr) obj->Render();
    }
    RenderHUD();
    SDL_RenderPresent(renderer);
}

void StageState::RenderHUD(){
    for (const auto& obj : HUDArray){
        if (obj != nullptr) obj->Render();
    }
}

void StageState::Run(){
    Resume();
}

void StageState::Start(){
    std::cout << Config::img["NAME"] << std::endl;
    img = new Img();
    img->SetPath(Config::img["NAME"]);
    if (Config::img["OPEN"] == "f"){
        img->SetSize(Config::name["SCREEN_WIDTH"], Config::name["SCREEN_HEIGHT"]);
        img->CreateImage();
    }
    else{
        img->SetSize(Config::name["SCREEN_WIDTH"], Config::name["SCREEN_HEIGHT"]);
        img->OpenImage();
    }
    img->SetPath(Config::img["CACHE"]);
    SDL_Surface* newSurface = img->GetSurfaceCopy();
    AddImg(newSurface);
    img->SaveImage();
    bg->Open(Config::img["CACHE"]);
    for (const auto& obj : objectArray){ obj->Start();}
    started = true;
}
void StageState::Pause(){}
void StageState::Resume(){
    if (!started){ Start();}
    dt = (int)Game::GetInstance().GetDeltaTime();
    while(!PopRequested()){
        dt = (int)Game::GetInstance().GetDeltaTime();
        Update();
        Render();
        // espera em uma proporcao de 30 fps(1000ms/30)
        // com a diferenca do tempo de processamento da ultima atualizacao
        if (1000/Config::name["FPS"] - dt > 0) SDL_Delay(1000/Config::name["FPS"] - dt);
        // SDL_Delay(1000/30);
    }
    Resources::Del();
    popRequested = true;
}
