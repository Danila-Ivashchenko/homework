#pragma once
#include <iostream>
#include "Board.h"
#include <conio.h>

class Viewer {
public:
	void print_starting_label();
	void print_menu();
	void print_exit();
	void print_shure_restart();
	void print_bot_message();
	void print_bot_message_error();
	void clear_window();
	void print_victory();
	int get_key();
	void print_board(Cell** arr);
};