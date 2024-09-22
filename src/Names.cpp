#include "Game_include.h"

// pensei em colcoar assim, mas e mais facil apenas usar define
namespace Colors{
    std::map<std::string,  SDL_Color> name = {
        {"BLACK", {0,0,0,0}},
        {"WHITE", {255,255,255,0}},
        {"RED", {255,0,0,0}},
        {"GREEN", {0,255,0,0}},
        {"BLUE", {0,0,255,0}}
    };
}

namespace Config{
    std::map<std::string, int> name = {
        {"PI", 3.14159},
        {"FPS", 30},
        {"SCREEN_WIDTH", 1024},
        {"SCREEN_HEIGHT", 600}
    };

    std::map<std::string, std::string> img = {
        {"CACHE", "Recursos/img/cache.png"},
        {"OPEN", "t"}
    };
}
