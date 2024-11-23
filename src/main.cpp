#include "Game.h"
#include "Utils.h"
#include <iostream>

int main()
{
    std::cout << Utils::remap2Dto1D({ 1,0 });
    Game game;
    game.run();
}
