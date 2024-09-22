#include "Game_include.h"

Sound::Sound(GameObject& associated)
    : Component(associated), chunk(nullptr){}
Sound::Sound(GameObject& associated, std::string file)
    : Component(associated){Open(file);}
Sound::~Sound(){}
void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
    if (chunk == nullptr) std::cout << "erro ao carregar o som! " << Mix_GetError() << std::endl;
}
bool Sound::IsOpen(){return (chunk != nullptr);}
void Sound::Play(int times){if (IsOpen()) channel = Mix_PlayChannel(-1, chunk, times-1);}
bool Sound::Playing(){
    if (IsOpen() && channel != -1) {return (Mix_Playing(channel) != 0);} else {return false;}
}
void Sound::Stop(){if (IsOpen()) Mix_HaltChannel(channel);}
void Sound::Update(float dt){}
void Sound::Render(){}
bool Sound::Is(std::string type) const{return (type == SOUND);}
void Sound::Start(){started = true;}
void Sound::NotifyCollision(GameObject& other){}
