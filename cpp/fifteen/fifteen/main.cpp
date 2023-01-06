#include <iostream>
#include "Board.h"
#include "Viewer.h"
#include "Game.h"
#include "Bot.h"
#include <conio.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    Viewer viewer;
    Board board;
    Game game(&board);
    Bot bot(&board);
    //game.engine();
    viewer.print_board(board.get_cells());
    //bot.move_zero_by_way(3, 2);
    //bot.move_zero_to_top(6);
    //bot.move_zero_to_left(6);
    //viewer.print_board(board.get_cells());
    //bot.move_zero_to_right(6);
    bot.move_value_to_pos(3);
    viewer.print_board(board.get_cells());
    //bot.move_zero(0, 0);
    //viewer.print_board(board.get_cells());
    //viewer.print_board(board.get_cells());

    //bot.move_zero_to_top(1);
    //viewer.print_board(board.get_cells());
    //for (;;) {
    //    ////viewer.clear_window();
    //    //int target = 3;
    //    ///*std::cin >> target;*/
    //    //bot.move_zero_to_left(target);
    //    //viewer.print_board(board.get_cells());
    //    //board.move(viewer.get_key());
    //}

    return 1;
}