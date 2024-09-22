#include "Game_include.h"

int main(int argc, char** argv) {

    Set_Config::Set_all();

    Game& game = Game::GetInstance();
    game.Run();
    game.~Game(); 

    return 0;
}
