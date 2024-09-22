#include "Game_include.h"

SoundEfect::SoundEfect(GameObject& associated, std::string file)
    : Sound(associated, file){
        // futuramente substiruir o construtor para que ele crie o proprio
        // GameObject, assim permitindo chamar o som pelo nome para que ele 
        // seja executado uma vez :)
        Play();
    }

void SoundEfect::Update(float dt){
    if(!Playing()) associated.RequestDelete();
}
