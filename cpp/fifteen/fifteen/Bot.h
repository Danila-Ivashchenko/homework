#pragma once
#include "Board.h"
#include <set>
#include <vector>
#include <queue>
#include <stack>

//
//class Bot {
//	Board* __board;
//	int __j_zero = 0, __i_zero = 0;
//	int __j_value = 0, __i_value = 0;
//public:
//	Bot(Board* board) : __board(board) {};
//	void keep_zero_cell();
//	void keep_target_cell(int value);
//	void move_target_on_position(int value);
//	int vertical_diff(int value);
//	int horizontal_diff(int value);
//
//	// передвижение кост€шек
//	//bool move_target_to_letf(int value);
//	//bool move_target_to_right(int value);
//	//bool move_target_to_bot(int value);
//	//bool move_target_to_top(int value);
//
//	// передвижение нулевой кост€шки
//	void move_zero_to_top(int value);
//	void move_zero_to_left(int value);
//	void move_zero_to_right(int value);
//};

struct Coords{
	int i = 0;
	int j = 0;
	Coords(int ai, int aj) : i(ai), j(aj) {};
};

class Bot {
	Board __board;
	std::set <int> fixed_cells;
	std::queue <int> moves_codes;
	int __i_zero = 0, __j_zero = 0;
	void fill_waves(int i_start, int j_start, int** map_cells, int siz, int i_end, int j_end);
	std::stack <Coords> make_way(int i_start, int j_start, int** map_cells, int size, int i_end, int j_end);
public:
	Bot(const Board& board) : __board(board) {};
	void keep_zero();
	Coords find_value(int value);
	std::stack <Coords> find_way(int i, int j);
	void move_zero(int i_needed, int j_needed);
	void move_zero_by_way(int i_needed, int j_needed);

	void move_zero_to_top(int value);
	void move_zero_to_bot(int value);
	void move_zero_to_left(int value);
	void move_zero_to_right(int value);

	void move_value_to_pos(int value);

	void set_board(Board board) { __board = board; };

	void calculate_moves();
	std::queue <int> get_moves_codes() { return moves_codes; };
};
