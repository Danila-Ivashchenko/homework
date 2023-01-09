#include "Bot.h"

void Bot::keep_zero() {
	for (int i = 0; i < __board.get_size(); i++) {
		for (int j = 0; j < __board.get_size(); j++) {
			if (__board.get_cells()[i][j].get_value() == 0) {
				__i_zero = i;
				__j_zero = j;
			}
		}
	}
}

void Bot::move_zero(int i_needed, int j_needed) {
	keep_zero();
	while (i_needed != __i_zero || j_needed != __j_zero) {
		if (j_needed != __j_zero) {
			if (j_needed > __j_zero) {
				__board.move(75); // zero идёт направо
				moves_codes.push(75);
				__j_zero++;
			}
			else if (j_needed < __j_zero) {
				__board.move(77); // zero идёт налево
				moves_codes.push(77);
				__j_zero--;
			}
		}
		if (i_needed != __i_zero) {
			if (i_needed > __i_zero) {
				__board.move(72); // zero идёт вниз
				moves_codes.push(72);
				__i_zero++;
			}
			else if (i_needed < __i_zero) {
				__board.move(80); // zero идёт вверх
				moves_codes.push(80);
				__i_zero--;
			}
		}
	}
}

void Bot::fill_waves(int i_start, int j_start, int** map_cells, int size, int i_end, int j_end) {
	int d = 1;
	if (!(i_start == i_end && j_start == j_end)) {
		if (i_start > 0 && map_cells[i_start - 1][j_start] == 0)
			map_cells[i_start - 1][j_start] = d;
		if (j_start > 0 && map_cells[i_start][j_start - 1] == 0)
			map_cells[i_start][j_start - 1] = d;
		if (i_start + 1 < size && map_cells[i_start + 1][j_start] == 0)
			map_cells[i_start + 1][j_start] = d;
		if (j_start + 1 < size && map_cells[i_start][j_start + 1] == 0)
			map_cells[i_start][j_start + 1] = d;
		d++;
		for (int c = 0; c < size + 1; c++) {
			if (map_cells[i_end][j_end] != 0)
				break;
			for (int i = 0; i < size; i++) {
				if (map_cells[i_end][j_end] != 0)
					break;
				for (int j = 0; j < size; j++) {
					if (map_cells[i_end][j_end] != 0)
						break;
					if (map_cells[i][j] == d - 1) {
						if (i > 0) {
							if (!(i - 1 == i_start && j == j_start) && map_cells[i - 1][j] == 0)
								map_cells[i - 1][j] = d;
						}
						if (j > 0) {
							if (!(i == i_start && j - 1 == j_start) && map_cells[i][j - 1] == 0)
								map_cells[i][j - 1] = d;
						}
						if (i + 1 < size) {
							if (!(i + 1 == i_start && j == j_start) && map_cells[i + 1][j] == 0)
								map_cells[i + 1][j] = d;
						}
						if (j + 1 < size) {
							if (!(i == i_start && j + 1 == j_start) && map_cells[i][j + 1] == 0)
								map_cells[i][j + 1] = d;
						}
					}
				}
			}
			d++;
		}
	}
}

std::stack<Coords> Bot::make_way(int i_start, int j_start, int** map_cells, int size, int i_end, int j_end)
{
	std::stack <Coords> made_way;
	int i = i_end, j = j_end;
	made_way.push(Coords(i_end, j_end));
	int d = map_cells[i_end][j_end];

	while ((i != i_start || j != j_start) && d != 1) {
		if (d < 0) {
			return std::stack <Coords>();
		}
		if (j + 1 < size && map_cells[i][j + 1] == d - 1) {
			j++;
		}
		else if (j > 0 && map_cells[i][j - 1] == d - 1) {
			j--;
		}
		else if (i + 1 < size && map_cells[i + 1][j] == d - 1) {
			i++;
		}
		else if (i > 0 && map_cells[i - 1][j] == d - 1) {
			i--;
		}
		made_way.push(Coords(i, j));
		d--;
	}


	for (int i = 0; i < size; i++)
		delete map_cells[i];
	delete map_cells;

	return made_way;
}

std::stack<Coords> Bot::find_way(int i_needed, int j_needed)
{
	keep_zero();
	std::stack <Coords> way;
	int size = __board.get_size();
	int** map_cells = new int* [size];
	Cell** board_cells = __board.get_cells();
	for (int i = 0; i < size; i++)
		map_cells[i] = new int[size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (fixed_cells.find(board_cells[i][j].get_value()) == fixed_cells.end()) {
				map_cells[i][j] = 0;
			}
			else {
				map_cells[i][j] = -1;
			}
		}
	}

	fill_waves(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
	return make_way(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
}

void Bot::move_zero_by_way(int i_needed, int j_needed) {
	std::stack <Coords> way = find_way(i_needed, j_needed);
	while (!way.empty()) {
		move_zero(way.top().i, way.top().j);
		way.pop();
	}
}

Coords Bot::find_value(int value)
{
	for (int i = 0; i < __board.get_size(); i++) {
		for (int j = 0; j < __board.get_size(); j++) {
			if (__board.get_cells()[i][j].get_value() == value) {
				return Coords(i, j);
			}
		}
	}
	return Coords(0, 0);
}


void Bot::move_zero_to_top(int value) {
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);

	if (value_coords.i > 0) {
		move_zero_by_way(value_coords.i - 1, value_coords.j);
	}
}

void Bot::move_zero_to_bot(int value) {
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);

	if (value_coords.i < __board.get_size() - 1) {
		move_zero_by_way(value_coords.i + 1, value_coords.j);
	}
}

void Bot::move_zero_to_left(int value) {
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	if (value_coords.j > 0) {
		move_zero_by_way(value_coords.i, value_coords.j - 1);
	}
}

void Bot::move_zero_to_right(int value) {
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	if (value_coords.j < __board.get_size() - 1) {
		move_zero_by_way(value_coords.i, value_coords.j + 1);
	}
}

void Bot::move_value_to_pos(int value) {
	Coords value_coords = find_value(value);

	int size = __board.get_size();
	int i_needed = (value - 1) / size;
	int j_needed = (value - 1) % size;
	int i_real = value_coords.i;
	int j_real = value_coords.j;
	bool is_corner_fight = (j_needed == size - 1);
	bool is_corner_bot = (j_needed == 0 && i_needed == size - 1);
	bool is_working_ok = true;

	fixed_cells.insert(value);


	if (i_needed + 1 == i_real && j_needed == j_real) {
		move_zero_to_top(value);
		keep_zero();
		if (__i_zero == i_needed && __j_zero == j_needed) {
			move_zero(i_real, j_real);
			i_real--;
		}
	}

	if (i_needed == i_real && j_needed + 1 == j_real) {
		move_zero_to_left(value);
		keep_zero();
		if (__i_zero == i_needed && __j_zero == j_needed) {
			move_zero(i_real, j_real);
			j_real--;
		}
	}

	if (i_needed != i_real || j_needed != j_real) {
		if (is_corner_fight)
			i_needed++;

		if (is_corner_bot)
			j_needed++;

		while ((j_needed != j_real || i_needed != i_real) && is_working_ok) {
			int last_moves_size = moves_codes.size(); // для контроля ошибки бота

			if (!is_working_ok) {
				break;
			}
			if (i_needed > i_real) {
				move_zero_to_bot(value);
				keep_zero();
				if (__i_zero == i_real + 1 && __j_zero == j_real)
					move_zero(i_real, j_real);
				Coords new_coords = find_value(value);
				if (new_coords.i == i_real + 1 && new_coords.j == j_real)
					i_real++;
			}

			if (j_needed > j_real) {
				move_zero_to_right(value);
				keep_zero();
				if (__i_zero == i_real && __j_zero == j_real + 1)
					move_zero(i_real, j_real);
				Coords new_coords = find_value(value);
				if (new_coords.i == i_real && new_coords.j == j_real + 1)
					j_real++;
			}
			if (j_needed < j_real) {
				move_zero_to_left(value);
				keep_zero();
				if (__i_zero == i_real && __j_zero == j_real - 1)
					move_zero(i_real, j_real);
				Coords new_coords = find_value(value);
				if (new_coords.i == i_real && new_coords.j == j_real - 1)
					j_real--;
			}

			if (i_needed < i_real) {
				move_zero_to_top(value);
				keep_zero();
				if (__i_zero == i_real - 1 && __j_zero == j_real)
					move_zero(i_real, j_real);
				Coords new_coords = find_value(value);
				if (new_coords.i == i_real - 1 && new_coords.j == j_real)
					i_real--;
			}
			if (moves_codes.size() == last_moves_size)
				is_working_ok = false;
			else
				is_working_ok = true;
		}

		if (is_corner_fight && is_working_ok) {
			move_zero_to_left(value);
			move_zero(i_needed, j_needed - 2);
			move_zero(i_needed - 1, j_needed - 2);
			move_zero(i_needed - 1, j_needed);
			move_zero(i_needed, j_needed);
			move_zero(i_needed, j_needed - 1);
			move_zero(i_needed - 1, j_needed - 1);
			move_zero(i_needed - 1, j_needed - 2);
			move_zero(i_needed, j_needed - 2);
		}
		if (is_corner_bot && is_working_ok) {
			move_zero_to_top(value);
			move_zero(i_needed - 2, j_needed);
			move_zero(i_needed - 2, j_needed - 1);
			move_zero(i_needed, j_needed - 1);
			move_zero(i_needed, j_needed);
			move_zero(i_needed - 1, j_needed);
			move_zero(i_needed - 1, j_needed - 1);
			move_zero(i_needed - 2, j_needed - 1);
			move_zero(i_needed - 2, j_needed);
		}
	}
}


void Bot::calculate_moves() {
	clear_all();
	int size = __board.get_size();
	for (int i = 0; i < size; i++) {
		move_value_to_pos(i + 1);
	}
	for (int i = 1; i < size; i++)
		move_value_to_pos(i * size + 1);

	bool is_working_ok = true;

	for (int i = 1; i < size && is_working_ok; i++)
		for (int j = 1; j < size && is_working_ok; j++)
			if (i * size + j + 1 < size * size) {
				move_value_to_pos(i * size + j + 1);
				Coords value_coords = find_value(i * size + j + 1);
				if (value_coords.i != i || value_coords.j != j)
					is_working_ok = false;
			}
}

//std::queue<int> Bot::solve_by_graph(){
//	std::queue <int> moves;
//	return find_moves_for_graph(__board, moves);
//}

//std::queue<int> Bot::find_moves_for_graph(Board primary_board, std::queue <int> last_moves) {
//
//}

//std::queue<int> Bot::find_moves_for_graph(Board primary_board, std::queue <int> last_moves){
//	Coords zero_coords = primary_board.find_zero();
//	std::queue <int> victory_moves;
//	if (last_moves.size() > 200) {
//		std::cout << "last_moves_count = " << last_moves.size() << std::endl;
//		return std::queue <int>();
//	}
//	if (zero_coords.i > 0) {
//		Board first_board = primary_board;
//		std::queue <int> first_queue_moves = last_moves;
//		first_board.move(80);
//		first_queue_moves.push(80);
//		std::cout << "first_board\nzero_coords: " << zero_coords.i << ", " << zero_coords.j << std::endl;
//		first_board.print();
//		if (first_board.victory()) {
//			if (victory_moves.empty())
//				victory_moves = first_queue_moves;
//		}
//		else if (first_queue_moves.size() < 200) {
//			victory_moves = find_moves_for_graph(first_board, first_queue_moves);
//		}
//			
//	}
//	if (zero_coords.i < primary_board.get_size() - 1) {
//		Board second_board = primary_board;
//		std::queue <int> second_queue_moves = last_moves;
//		second_board.move(72);
//		second_queue_moves.push(72);
//		std::cout << "second_board\nzero_coords: " << zero_coords.i << ", " << zero_coords.j << std::endl;
//		second_board.print();
//		if (second_board.victory()) {
//			if (victory_moves.empty())
//				victory_moves = second_queue_moves;
//		}
//		else if (second_queue_moves.size() < 200) {
//			std::queue <int> buf_queue = find_moves_for_graph(second_board, second_queue_moves);
//			if (buf_queue.size() > victory_moves.size())
//				victory_moves = buf_queue;
//		}
//	}
//	if (zero_coords.j > 0) {
//		Board third_board = primary_board;
//		std::queue <int> third_queue_moves = last_moves;
//		third_board.move(77);
//		third_queue_moves.push(77);
//		std::cout << "third_board\nzero_coords: " << zero_coords.i << ", " << zero_coords.j << std::endl;
//		third_board.print();
//		if (third_board.victory()) {
//			if (victory_moves.empty())
//				victory_moves = third_queue_moves;
//		}
//		else if (third_queue_moves.size() < 200) {
//			std::queue <int> buf_queue = find_moves_for_graph(third_board, third_queue_moves);
//			if (buf_queue.size() > victory_moves.size())
//				victory_moves = buf_queue;
//		}
//	}
//	if (zero_coords.j < primary_board.get_size() - 1) {
//		Board fourth_board = primary_board;
//		std::queue <int> fourth_queue_moves = last_moves;
//		fourth_board.move(75);
//		fourth_queue_moves.push(75);
//		std::cout << "fourth_board\nzero_coords: " << zero_coords.i << ", " << zero_coords.j << std::endl;
//		fourth_board.print();
//		if (fourth_board.victory()) {
//			if (victory_moves.empty())
//				victory_moves = fourth_queue_moves;
//		}
//		else if (fourth_queue_moves.size() < 200) {
//			std::queue <int> buf_queue = find_moves_for_graph(fourth_board, fourth_queue_moves);
//			if (buf_queue.size() > victory_moves.size())
//				victory_moves = buf_queue;
//		}
//	}
//
//
//}

//std::queue<int> Bot::find_moves_for_graph(Board primary_board, std::queue <int> last_moves) {
//	Coords zero_coords = primary_board.find_zero();
//	Board first_board = primary_board;
//	Board second_board = primary_board;
//	Board third_board = primary_board;
//	Board fourth_board = primary_board;
//
//	std::queue <int> first_queue_moves = last_moves;
//	std::queue <int> second_queue_moves = last_moves;
//	std::queue <int> third_queue_moves = last_moves;
//	std::queue <int> fourth_queue_moves = last_moves;
//	if (zero_coords.i > 0) {
//		first_board.move(80);
//		first_queue_moves.push(80);
//	}
//	if (zero_coords.i < primary_board.get_size() - 1) {
//		second_board.move(72);
//		second_queue_moves.push(72);
//	}
//	if (zero_coords.j > 0) {
//		third_board.move(77);
//		third_queue_moves.push(77);
//	}
//	if (zero_coords.j < primary_board.get_size() - 1) {
//		fourth_board.move(75);
//		fourth_queue_moves.push(75);
//	}
//	if (first_board.victory())
//		return first_queue_moves;
//
//}


void Bot::clear_all(){
	while (!moves_codes.empty())
		moves_codes.pop();

	while (!fixed_cells.empty()){
		fixed_cells.erase(fixed_cells.begin());
	}
}