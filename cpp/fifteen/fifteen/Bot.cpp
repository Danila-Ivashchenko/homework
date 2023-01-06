#include "Bot.h"
//
//
//void Bot::keep_zero_cell() {
//	for (int i = 0; i < __board->get_size(); i++) {
//		for (int j = 0; j < __board->get_size(); j++) {
//			if (__board->get_cells()[i][j].get_value() == 0) {
//				__i_zero = i;
//				__j_zero = j;
//			}
//		}
//	}
//}
//
//
//void Bot::keep_target_cell(int value) {
//	for (int i = 0; i < __board->get_size(); i++) {
//		for (int j = 0; j < __board->get_size(); j++) {
//			if (__board->get_cells()[i][j].get_value() == value) {
//				__i_value = i;
//				__j_value = j;
//			}
//		}
//	}
//}
//
//
//int Bot::vertical_diff(int value) {
//	keep_target_cell(value);
//	keep_zero_cell();
//	return __i_zero - __i_value;
//	
//}
//
//int Bot::horizontal_diff(int value) {
//	keep_target_cell(value);
//	keep_zero_cell();
//	return __j_zero - __j_value;
//}
//
//void Bot::move_zero_to_top(int value) {
//	int v_diff = vertical_diff(value);
//	int h_diff = horizontal_diff(value);
//	int size = __board->get_size();
//	//std::cout << "i_value = " << __i_value << " j_value = " << __j_value << "\n";
//	if (__i_value != 0) {
//		while (v_diff != -1 || h_diff != 0) {
//			keep_zero_cell();
//			if (v_diff != -1 && h_diff >= 0) {
//				if (v_diff < 0) {
//					__board->move(72);
//					v_diff++;
//				}
//				else if (v_diff == 1) {
//					if (h_diff == 0) {
//						if (__j_zero < size - 1) {
//							__board->move(75);
//							__board->print();
//							__board->move(80);
//							__board->print();
//							__board->move(80);
//							__board->print();
//							__board->move(77);
//							__board->print();
//						}
//						else {
//							__board->move(77);
//							__board->print();
//							__board->move(80);
//							__board->print();
//							__board->move(80);
//							__board->print();
//							__board->move(75);
//							__board->print();
//						}
//						v_diff -= 2;
//					}
//					else {
//						__board->move(80);
//						v_diff--;
//					}
//				}
//				else {
//					__board->move(80);
//					v_diff--;
//				}
//			}
//			if (h_diff != 0) {
//				if (h_diff == -1) {
//					__board->move(72);
//					__board->move(77);
//					h_diff++;
//					v_diff--;
//				}
//				else if (h_diff < 0) {
//					__board->move(75);
//					h_diff++;
//				}
//				else if (h_diff > 0) {
//					__board->move(77);
//					h_diff--;
//				}
//			}
//		}
//	}
//}
//
//void Bot::move_zero_to_left(int value){
//	int v_diff = vertical_diff(value);
//	int h_diff = horizontal_diff(value);
//	int size = __board->get_size();
//	//std::cout << "h_diff = " << h_diff << std::endl;
//	//__board->print();
//	if (__j_value != 0) {
//		while (v_diff != 0 && h_diff != -1) {
//			keep_zero_cell();
//			//std::cout << v_diff << ", " << h_diff << std::endl;
//			if (v_diff != 0) {
//				if (v_diff == 1 && h_diff == 0) {
//					std::cout << "here\n";
//					__board->move(77);
//					__board->move(72);
//					__board->move(72);
//					__board->move(75);
//					__board->move(75);
//					__board->move(80);
//					v_diff--;
//					h_diff--;
//				}
//				else if (v_diff < 0) {
//					__board->move(72);
//					v_diff++;
//				}
//				else if (v_diff > 0){
//					__board->move(80);
//					v_diff--;
//				}
//			}
//			if (h_diff != -1 && v_diff == 0) {
//				if (h_diff < -1) {
//					__board->move(75);
//					h_diff++;
//				}
//				else if (h_diff == 1) {
//					//std::cout << "v_diff = " << v_diff << std::endl;
//					if (v_diff == 0) {
//						if (__i_zero < size - 1) {
//							__board->move(72);
//							__board->move(77);
//							__board->move(77);
//							__board->move(80);
//						}
//						else {
//							__board->move(80);
//							__board->move(77);
//							__board->move(77);
//							__board->move(72);
//						}
//						h_diff -= 2;
//					}
//					else {
//						__board->move(77);
//						h_diff--;
//					}
//				}
//				else if (h_diff > -1) {
//					__board->move(77);
//					h_diff--;
//				}
//				//__board->print();
//			}
//			__board->print();
//
//		}
//	}
//}
//
//void Bot::move_zero_to_right(int value) {
//	int v_diff = vertical_diff(value);
//	int h_diff = horizontal_diff(value);
//	int size = __board->get_size();
//		while (v_diff != 0) {
//			keep_zero_cell();
//			//std::cout << v_diff << ", " << h_diff << std::endl;
//			if (v_diff != 0 && h_diff == 1) {
//				if (v_diff < 0) {
//					__board->move(72);
//					v_diff++;
//				}
//				else if (v_diff > 0) {
//					__board->move(80);
//					v_diff--;
//				}
//				//__board->print();
//			}
//			if (h_diff != 1 && v_diff == 0) {
//				//std::cout << 
//				if (h_diff > 1) {
//					__board->move(77);
//					h_diff--;
//				}
//				else if(h_diff == -1){
//					//std::cout << "here\n";
//					if (v_diff == 0) {
//						if (__i_zero < size - 1) {
//							__board->move(72);
//							//__board->print();
//							__board->move(75);
//							//__board->print();
//							__board->move(75);
//							//__board->print();
//							__board->move(80);
//							//__board->print();
//						}
//						else {
//							__board->move(80);
//							//__board->print();
//							__board->move(75);
//							//__board->print();
//							__board->move(75);
//							//__board->print();
//							__board->move(72);
//							//__board->print();
//						}
//						h_diff += 2;
//					}
//					else {
//						__board->move(75);
//						h_diff++;
//					}
//				}
//				else if (h_diff < 1) {
//					__board->move(75);
//					h_diff++;
//				}	
//				//__board->print();
//			}
//		}
//}
//
//void Bot::move_target_on_position(int value) {
//	int size = __board->get_size();
//	int i_needed = (value - 1) / size;
//	int j_needed = (value - 1) % size;
//	keep_target_cell(value);
//	std::cout << i_needed << ", " << j_needed << std::endl;
//	std::cout << __i_value << ", " << __j_value << std::endl;
//
//	while(j_needed != __j_value) {
//	//for (int i = 0; i < abs(j_needed - __j_value); i++){
//		if (j_needed > __j_value) {
//			std::cout << "to right\n";
//			move_zero_to_right(value);
//			//__board->print();
//			__board->move(77);
//			//__board->print();
//			__j_value++;
//
//		}
//		else {
//			std::cout << "to left\n";
//			move_zero_to_left(value);
//			__board->move(75);
//			__j_value--;
//		}
//		//__board->print();
//	}
//	while (i_needed != __i_value) {
//	//for (int i = 0; i <= abs(i_needed - __i_value); i++){
//		if (i_needed < __i_value) {
//			std::cout << "to top\n";
//			move_zero_to_top(value);
//			__board->print();
//			__board->move(72);
//			__board->print();
//			__i_value--;
//		}
//	}
//	__board->print();
//}


void Bot::keep_zero() {
	for (int i = 0; i < __board->get_size(); i++) {
		for (int j = 0; j < __board->get_size(); j++) {
			if (__board->get_cells()[i][j].get_value() == 0) {
				__i_zero = i;
				__j_zero = j;
			}
		}
	}
}

void Bot::move_zero(int i_needed, int j_needed) {
	keep_zero();
	//std::cout << __i_zero << ", " << __j_zero << std::endl;
	while (i_needed != __i_zero || j_needed != __j_zero) {
		if (j_needed != __j_zero) {
			if (j_needed > __j_zero) {
				__board->move(75); // zero идёт направо
				__j_zero++;
			}
			else if (j_needed < __j_zero) {
				__board->move(77); // zero идёт налево
				__j_zero--;
			}
		}
		if (i_needed != __i_zero) {
			if (i_needed > __i_zero) {
				__board->move(72); // zero идёт вниз
				__i_zero++;
			}
			else if (i_needed < __i_zero) {
				__board->move(80); // zero идёт вверх
				__i_zero--;
			}
		}
		std::cout << __i_zero << ", " << __j_zero << std::endl;
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
	//std::cout << "i = " << i << ", j = " << j << ", d = " << d << std::endl;
	while (i != i_start || j != j_start) {
		
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
	return made_way;
}

std::stack<Coords> Bot::find_way(int i_needed, int j_needed)
{
	keep_zero();
	std::stack <Coords> way;
	int size = __board->get_size();
	int** map_cells = new int * [size];
	Cell** board_cells = __board->get_cells();
	for (int i = 0; i < size; i++)
		map_cells[i] = new int[size];
	//std::cout << "fixed values:\n";
	//for (auto v : fixed_cells)
	//	std::cout << v << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (fixed_cells.find(board_cells[i][j].get_value()) == fixed_cells.end()) {
				map_cells[i][j] = 0;
			}
			else {
				//std::cout << "i = " << i << ", j = " << j << " , value = " << board_cells[i][j].get_value() << "!!!!!\n";
				map_cells[i][j] = -1;
			}
		}
	}
	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		std::cout << map_cells[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	fill_waves(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		std::cout << map_cells[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	return make_way(__i_zero, __j_zero, map_cells, size, i_needed, j_needed);
}

void Bot::move_zero_by_way(int i_needed, int j_needed){
	//std::cout << "need " << i_needed << ", " << j_needed << std::endl;
	std::stack <Coords> way = find_way(i_needed, j_needed);
	std::cout << way.size() << std::endl;
	while (!way.empty()) {
		//std::cout << way.top().i << ", " << way.top().j << std::endl;
		move_zero(way.top().i, way.top().j);
		way.pop();
		//__board->print();
	}
}

Coords Bot::find_value(int value)
{
	for (int i = 0; i < __board->get_size(); i++) {
		for (int j = 0; j < __board->get_size(); j++) {
			if (__board->get_cells()[i][j].get_value() == value) {
				return Coords(i, j);
			}
		}
	}
}


void Bot::move_zero_to_top(int value){
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);
	
	if (value_coords.i > 0) {
		//std::cout << value_coords.i - 1 << " ,,, " << value_coords.j << std::endl;
		move_zero_by_way(value_coords.i - 1, value_coords.j);
	}
}

void Bot::move_zero_to_bot(int value) {
	//keep_zero();
	fixed_cells.insert(value);
	Coords value_coords = find_value(value);

	if (value_coords.i < __board->get_size() - 1) {
		//std::cout << value_coords.i + 1 << " ,,, " << value_coords.j << std::endl;
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
	if (value_coords.j < __board->get_size() - 1) {
		//std::cout << value_coords.i << " ,,, " << value_coords.j + 1 << std::endl;
		move_zero_by_way(value_coords.i, value_coords.j + 1);
	}
}

void Bot::move_value_to_pos(int value){
	Coords value_coords = find_value(value);
	int i_needed = (value - 1) / __board->get_size();
	int j_needed = (value - 1) % __board->get_size();
	int i_real = value_coords.i;
	int j_real = value_coords.j;
	std::cout << i_needed << ", " << j_needed << std::endl;
	std::cout << i_real << ", " << j_real << std::endl;
	while (i_needed != i_real || j_needed != j_real) {
		if (i_needed < i_real) {
			std::cout << 1 << std::endl;
			move_zero_to_top(value);
			__board->move(72);
			i_real--;
		}
		if (i_needed > i_real) {
			std::cout << 2 << std::endl;
			move_zero_to_bot(value);
			__board->move(80);
			i_real++;
		}
		if (j_needed < j_real) {
			std::cout << 3 << std::endl;
			move_zero_to_right(value);
			__board->move(77);
			j_real--;
		}
		if (j_needed < j_real) {
			std::cout << 4 << std::endl;
			move_zero_to_left(value);
			__board->move(75);
			j_real++;
		}
	}
}