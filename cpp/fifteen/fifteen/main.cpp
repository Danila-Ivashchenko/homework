#include <iostream>
#include "Board.h"
#include "Viewer.h"
#include "Game.h"
#include "Bot.h"
#include <conio.h>
#include <memory>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    Board board;
    Game game(&board);

    game.engine();

    return 1;
}