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
	////std::cout << __i_zero << ", " << __j_zero << std::endl;
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
		//__board.print();
		//std::cout << __i_zero << ", " << __j_zero << std::endl;
	}
}

void Bot::fill_waves(int i_start, int j_start, int** map_cells, int size, int i_end, int j_end) {
	//std::cout << "need to go " << i_end << ", " << j_end << std::endl;
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
	////std::cout << "i = " << i << ", j = " << j << ", d = " << d << std::endl;
	
	while ((i != i_start || j != j_start) && d != 1) {
		if (d < 0) {
			return std::stack <Coords>();
		}
		//std::cout << "ping " << "i = " << i << " j = " << j << ", d = " << d << std::endl;
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
	int** map_cells = new int * [size];
	Cell** board_cells = __board.get_cells();
	for (int i = 0; i < size; i++)
		map_cells[i] = new int[size];
	////std::cout << "fixed values:\n";
	//for (auto v : fixed_cells)
	//	//std::cout << v << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (fixed_cells.find(board_cells[i][j].get_value()) == fixed_cells.end()) {
				map_cells[i][j] = 0;
			}
			else {
				////std::cout << "i = " << i << ", j = " << j << " , value = " << board_cells[i][j].get_value() << "!!!!!\n";
				map_cells[i][j] = -1;
			}
		}
	}

	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		//std::cout << map_cells[i][j] << " ";
	//	}
	//	//std::cout << std::endl;
	//}
	fill_waves(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//std::cout << map_cells[i][j] << " ";
		}
		//std::cout << std::endl;
	}
	//std::cout << "i_needed - " << i_needed << ", j_needed - " << j_needed << std::endl;
	return make_way(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
}

void Bot::move_zero_by_way(int i_needed, int j_needed){
	//std::cout << "need " << i_needed << ", " << j_needed << std::endl;
	std::stack <Coords> way = find_way(i_needed, j_needed);
	//std::cout << way.size() << std::endl;
	while (!way.empty()) {
		////std::cout << way.top().i << ", " << way.top().j << std::endl;
		move_zero(way.top().i, way.top().j);
		way.pop();
	//__board.print();
	}
}

Coords Bot::find_value(int value)
{
	for (int i = 0; i < __board.get_size(); i++) {
		for (int j = 0; j < __board.get_size(); j++) {
			if (__board.get_cells()[i][j].get_value() == value) {
				//std::cout << "VALUE = " << value << ", COORDS = " << i << " " << j << std::endl;
				return Coords(i, j);
			}
		}
	}
	return Coords(0, 0);
}


void Bot::move_zero_to_top(int value){
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	
	if (value_coords.i > 0) {
		////std::cout << value_coords.i - 1 << " ,,, " << value_coords.j << std::endl;
		move_zero_by_way(value_coords.i - 1, value_coords.j);
	}
}

void Bot::move_zero_to_bot(int value) {
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);

	if (value_coords.i < __board.get_size() - 1) {
		////std::cout << value_coords.i + 1 << " ,,, " << value_coords.j << std::endl;
		move_zero_by_way(value_coords.i + 1, value_coords.j);
	}
}

void Bot::move_zero_to_left(int value) {
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	if (value_coords.j > 0) {
		//std::cout << value_coords.i << " ,,, " << value_coords.j - 1 << std::endl;
		move_zero_by_way(value_coords.i, value_coords.j - 1);
	}
}

void Bot::move_zero_to_right(int value) {
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	if (value_coords.j < __board.get_size() - 1) {
		////std::cout << value_coords.i << " ,,, " << value_coords.j + 1 << std::endl;
		move_zero_by_way(value_coords.i, value_coords.j + 1);
	}
}

void Bot::move_value_to_pos(int value){
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

	if (__status != 2) { // если не случалось ошибки в работе бота

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

			if (is_corner_bot) {
				j_needed++;
			}

			while ((j_needed != j_real || i_needed != i_real) && is_working_ok) {
				int last_moves_size = moves_codes.size(); // для контроля ошибки бота
				if (!is_working_ok) {
					__status = 2;
					int a;
					std::cin >> a;
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
				std::cout << last_moves_size << " " << moves_codes.size() << std::endl;
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
}


void Bot::calculate_moves(){
	__status = 1;
	//std::cout << "hello\n";

	while (!moves_codes.empty())
		moves_codes.pop();

	int size = __board.get_size();
	for (int i = 0; i < size; i++) {
		move_value_to_pos(i + 1);
		//std::cout << "hello\n";
	}
	for (int i = 1; i < size; i++)
		move_value_to_pos(i * size + 1);

	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i * size + j + 1 < size * size) {
				move_value_to_pos(i * size + j + 1);
				//std::cout << "hello\n";
			}
}