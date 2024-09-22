#include "Game_include.h"

GameObject::GameObject() : isDeath(false), angleDeg(0), started(false) {}
GameObject::~GameObject(){
    // for que percorre do início da direita (rbegin) ao final da direita (rend) e deleta todo o vetor
    for (auto component = components.rbegin(); component != components.rend(); ++component){ RemoveComponent(*component);}
    components.clear();
}
void GameObject::Update(float dt){
    for (const auto& component : components){ 
        if (component != nullptr) component->Update(dt);
    }
}
void GameObject::Render(){
    for (const auto& component : components){ 
        if (component != nullptr) component->Render();
    }
}
bool GameObject::IsDeath(){ return isDeath;}
void GameObject::RequestDelete(){ isDeath = true;}
void GameObject::AddComponent(Component* cpt){components.push_back(cpt);}
void GameObject::RemoveComponent(Component* cpt){
    int delIndex = -1;
    for (size_t i=0; i < components.size(); ++i){
        if (cpt == components[i]) {
            delIndex = i; 
            break;
        }
    }
    if (delIndex != -1){
        delete components[delIndex];
        components.erase(components.begin() + delIndex);
    }
}
Component* GameObject::GetComponent(std::string type){
    for (const auto& component : components){
        // verifica o tipo, se for o desejado, devolve o componente
        if (component->Is(type)) return component;
    }
    return nullptr;
}
void GameObject::Start(){
    for(const auto& component : components){ component->Start();}
    started = true;
}
// a ideia e notificar os componentes apenas se eles sao do time oposto
void GameObject::NotifyCollision(GameObject& other){

}
