#include "Game_include.h"

CameraFollower::CameraFollower(GameObject& associated, int x, int y): Component(associated), pos(Vec2(x, y)){}
void CameraFollower::Update(float dt){
    associated.box.x = Camera::pos.x + pos.x;
    associated.box.y = Camera::pos.y + pos.y;
}
void CameraFollower::Render(){}
bool CameraFollower::Is(std::string type) const{return (type == "CameraFollower");}
void CameraFollower::Start(){started = true;}
void CameraFollower::NotifyCollision(GameObject& other){}
