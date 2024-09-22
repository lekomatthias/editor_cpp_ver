#include "Game_include.h"

void StageState::UsersCommands(){
    int mouseX = input->GetMouseX() + Camera::pos.x;
    int mouseY = input->GetMouseY() + Camera::pos.y;
    if (input->IsMouseDown(SDL_BUTTON_LEFT)){
        if (mouseX < Config::name["SCREEN_WIDTH"] && 0 <= mouseX &&
            mouseY < Config::name["SCREEN_HEIGHT"] && 0 <= mouseY){
            if (input->MousePress(SDL_BUTTON_LEFT)){ NewLayer(mouseX, mouseY, Colors::name["BLACK"]);}
            else{ OverrideLayer(mouseX, mouseY, Colors::name["BLACK"]);}
            posX = mouseX;
            posY = mouseY;
        }
    }
    if (input->IsKeyDown(SDLK_CTRL)){
        if (input->KeyPress(SDLK_s)){
            img->SetPath(Config::img["SAVE_NAME"]);
            img->SaveImage();
            std::cout << "imagem salva em '" << Config::img["SAVE_NAME"] <<"'" << std::endl;
            img->SetPath(Config::img["CACHE"]);
        }
        if (input->KeyPress(SDLK_z)){
            if(!input->IsKeyDown(SDLK_LSHIFT)){
                if (surfaceArray.size() > 1){
                    BackImg();
                    std::cout << "imagens na pilha: " << surfaceArray.size() << std::endl;
                }
            }else{
                if (redoSurfaceArray.size()){
                    ReDo();
                    std::cout << "imagens na pilha redo: " << redoSurfaceArray.size() << std::endl;
                }
            }
        }

    }
    if (input->QuitRequested()) popRequested = true;
    for (const auto& obj : objectArray){
        if (obj != nullptr) obj->Update(dt);
    }
}