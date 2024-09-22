#include "Game_include.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(1, 1);

void Camera::Follow(GameObject* newFocus) { focus = newFocus;}
void Camera::Unfollow() { focus = nullptr;}
void Camera::Zero(){ pos = Vec2(0, 0);}
void Camera::Update(float dt) {
    if (focus != nullptr) {
        pos = Vec2((float)(focus->box.x + focus->box.w/2 - Game::GetInstance().GetWidth()/2),
                   (float)(focus->box.y + focus->box.h/2 - Game::GetInstance().GetHeight()/2));
    }
    else {
        InputManager* input = &InputManager::GetInstance();
        // andar com setas
        if (input->IsKeyDown(SDLK_LEFT)) pos.x -= (int)(speed.x * dt);
        if (input->IsKeyDown(SDLK_RIGHT)) pos.x += (int)(speed.x * dt);
        if (input->IsKeyDown(SDLK_UP)) pos.y -= (int)(speed.y * dt);
        if (input->IsKeyDown(SDLK_DOWN)) pos.y += (int)(speed.y * dt);
    }
}
