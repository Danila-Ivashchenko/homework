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
    Bot bot(board);

    //bot.calculate_moves();
    game.engine();
    //bot.move_zero_by_way(3, 2);
    //bot.move_zero_to_top(6);
    //bot.move_zero_to_left(6);
    //viewer.print_board(board.get_cells());
    //bot.move_zero_to_right(6);
    //bot.move_value_to_pos(1);
    //bot.move_value_to_pos(2);
    //bot.move_value_to_pos(3);    
    //bot.move_value_to_pos(4);    
    //bot.move_value_to_pos(5);    
    //bot.move_value_to_pos(9);
    //bot.move_value_to_pos(13);
    //bot.move_value_to_pos(6);
    //bot.move_value_to_pos(7);
    //bot.move_value_to_pos(8);
    //bot.move_value_to_pos(10);

    //std::queue <int> codes = bot.get_moves_codes();
    //std::cout << "moves count = " << codes.size();

    //while (!codes.empty()) {
    //    //viewer.clear_window();
    //    std::cout << codes.front() << std::endl;
    //    board.move(codes.front());
    //    viewer.print_board(board.get_cells());
    //    codes.pop();
    //    std::cout << _getch();
    //}

    //bot.move_value_to_pos(11);
    //bot.move_value_to_pos(12);
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