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
    case 5:
        break;
    default:
        break;
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
    while (code != 109 && code != 27)
        if (code == 27) {
            exit();
            break;
        } else
            code = viewer.get_key();
    if (code == 109)
        __status = 1;
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