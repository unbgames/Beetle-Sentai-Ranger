#include "Game.h"
#include "Stage1.h"

int main (int argc, char** argv) {

    Game* game;

    srand(time(NULL));

    game = Game::GetInstance();
    game->Push(new Stage1(4));
    game->Run();
    delete game;

    return 0;
}
