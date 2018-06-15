#include "Game.h"
#include "Stage1.h"
#include "MainMenu.h"

int main (int argc, char** argv) {

    Game* game;

    srand(time(NULL));

    game = Game::GetInstance();
    game->Push(new MainMenu());
    game->Run();
    delete game;

    return 0;
}
