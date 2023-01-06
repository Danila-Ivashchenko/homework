#include "Game.h"


void Game::render() {
    switch (__status){
    case 0:
        start();
        break;
    case 1:
        play();
        break;
    case 2:
        restart();
        break;
    case 3:
        menu();
        break;
    case 4:
        bot_mod();
        break;
    case 5:
        break;
    default:
        break;
    }
}

void Game::bot_mod() {
    __bot = Bot(*__board);
    __bot.set_board(*__board);
    __bot.calculate_moves();
    std::queue <int> moves = __bot.get_moves_codes();
    int code = 0;
    while (!moves.empty() && code != 104 && code != 109) {
        viewer.clear_window();
        __board->move(moves.front());
        moves.pop();
        viewer.print_board(__board->get_cells());
        code = viewer.get_key();
    }
    while (code != 104 && code != 109) {
        code = viewer.get_key();
        if (code == 109)
            __status = 3;
        else if (code == 104)
            __status = 1;
    }
}

void Game::start() {
	viewer.print_starting_label();
	int code = viewer.get_key();

    while (code != 13) {
        code = viewer.get_key();
    }
    __status = 1;
}


void Game::play() {
    Cell** cells = __board->get_cells();
    viewer.clear_window();
    viewer.print_board(cells);
    for (;;) {
        if (!__board->victory()) {
            int code = viewer.get_key();
            if (code == 109) {
                __status = 3;
                break;
            }
            else if (code == 104) {
                __status = 4;
                break;
            }
            else {
                __board->move(code);
                viewer.clear_window();
                viewer.print_board(cells);
            }
        }
        else {
            __status = 2;
        }
    }
}

void Game::menu() {
    viewer.clear_window();
    viewer.print_menu();
    int code = viewer.get_key();
    while (code != 109 && code != 27 && code != 104) {
        if (code == 27) {
            exit();
            break;
        }
        else
            code = viewer.get_key();
    }
    std::cout << code << std::endl;
    if (code == 109)
        __status = 1;
    if (code == 104)
        __status = 4;
}


void Game::restart() {
    viewer.print_victory();
    int code = viewer.get_key();
    while (code != 13)
        code = viewer.get_key();
    __status = 1;
}

void Game::exit() {
    viewer.print_exit();
    int code = viewer.get_key();
    if (code == 13)
        __status = 5;
}


void Game::engine() {
    while (__status != 5) {
        render();
    }
}