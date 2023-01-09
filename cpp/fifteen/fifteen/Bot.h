#pragma once
#include "Board.h"
#include <set>
#include <vector>
#include <queue>
#include <stack>

class Bot {
	Board __board;

	std::set <int> fixed_cells;
	std::queue <int> moves_codes;
	int __i_zero = 0, __j_zero = 0;
	void fill_waves(int i_start, int j_start, int** map_cells, int siz, int i_end, int j_end);
	std::stack <Coords> make_way(int i_start, int j_start, int** map_cells, int size, int i_end, int j_end);
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
	void clear_all();

	std::queue <int> find_moves_for_graph(Board primary_board, std::queue <int> last_moves);
public:
	Bot(const Board& board) : __board(board) {};

	void set_board(Board board) { __board = board; };

	void calculate_moves();
	std::queue <int> get_moves_codes() { return moves_codes; };
	std::queue <int> solve_by_graph();
};
