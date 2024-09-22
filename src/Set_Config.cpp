#include "Game_include.h"

void Set_Config::Set_open_img(){
    while (true){
        std::cout << "Deseja criar[c] ou editar uma imagem[e]?" << std::endl;
        std::string name;
        std::cin >> name;
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);
        if (name == "E"){
            Config::img["OPEN"] = "t";
            break;
        }
        if (name == "C"){
            Config::img["OPEN"] = "f";
            break;
        }
        std::cout << "a respota deve ser ou 'e' ou 'c'!" << std::endl << std::endl;
    }
}
void Set_Config::Set_img_name(){
    std::cout << "digite o nome da imagem: " << std::endl;
    std::string name;
    std::cin >> name;
    Config::img.insert(make_pair("NAME", "Recursos/img/" + name + ".png"));
    if (Config::img["OPEN"] == "f"){ Config::img.insert(make_pair("SAVE_NAME", "Recursos/img/" + name + ".png"));}
    else {Config::img.insert(make_pair("SAVE_NAME", "Recursos/img/" + name + "(editada).png"));}
}
void Set_Config::Set_img_size(){
    std::cout << "digite a largura da imagem: " << std::endl;
    int x;
    std::cin >> x;
    Config::name["SCREEN_WIDTH"] = x;

    std::cout << "digite a altura da imagem: " << std::endl;
    std::cin >> x;
    Config::name["SCREEN_HEIGHT"] = x;
}
void Set_Config::Set_img_newname(){}
void Set_Config::Set_all(){
    Set_open_img();
    Set_img_name();
    if (Config::img["OPEN"] == "f") Set_img_size();
    else {
        SDL_Surface* imgSurface = IMG_Load(Config::img["NAME"].c_str());
        Config::name["SCREEN_WIDTH"] = imgSurface->w;
        Config::name["SCREEN_HEIGHT"] = imgSurface->h;
        SDL_FreeSurface(imgSurface);
    }
}