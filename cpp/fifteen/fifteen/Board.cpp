#include "Board.h"

std::ostream& operator<<(std::ostream& out, Cell& cell)
{
	std::cout << std::setw(2);
	if (cell.__value == 0)
		out << "  ";
	else
		out << cell.__value;
	return out;
}

Board::Board() {
	for (int i = 0; i < size; i++) {
		__cells[i] = new Cell[size];
		for (int j = 0; j < size; j++) {
			__cells[i][j].set_value((i * size + j + 1) % 16);
			__cells[i][j].set_coords(j, i);
		}
	}
	shake();
}

Board::Board(const Board& other){
	size = other.size;
	for (int i = 0; i < size; i++) {
		__cells[i] = new Cell[size];
		for (int j = 0; j < size; j++) {
			__cells[i][j].set_value(other.__cells[i][j].get_value());
		}
	}
}

void Board::shake()
{
	srand((unsigned)time(0));

	for (int i = 0; i < size * size * size; i++) {
		int k = rand() % 5;
		switch (k)
		{
		case 0:
			move_zero_cell(size - 1, 0);
			move_zero_cell(0, 0);
			move_zero_cell(0, size - 1);
			move_zero_cell(size - 1, size - 1);
			break;
		case 1:
			for (int j = 0; j < size - 1; j++) {
				move_zero_cell(size - j, 0);
				move_zero_cell(size - j - 1, 0);
				move_zero_cell(size - j - 1, size - 1);
			}
			move_zero_cell(size - 1, size - 1);
			break;
		case 3:
			for (int j = 0; j < size - 1; j++) {
				move_zero_cell(0, size - j);
				move_zero_cell(0, size - j - 1);
				move_zero_cell(size - 1, size - j - 1);
			}
			move_zero_cell(size - 1, size - 1);
			break;
		case 4:
			move_zero_cell(0, 0);
			move_zero_cell(0, size - 1);
			move_zero_cell(size - 1, 0);
			move_zero_cell(size - 1, size - 1);
			break;
		default:
			break;
		}
	}
	move_zero_cell(rand() % size, rand() % size);
}

void Board::move_zero_cell(int i_needed, int j_needed){
	int i_zero = 0, j_zero = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			if (__cells[i][j].get_value() == 0) {
				i_zero = i;
				j_zero = j;
			}
	}
	while (i_needed != i_zero || j_needed != j_zero) {
		if (i_needed < 0 || i_needed >= size || j_needed < 0 || j_needed >= size)
			break;
		if (j_needed != j_zero) {
			if (j_needed > j_zero) {
				move(75); // zero идёт направо
				j_zero++;
			}
			else if (j_needed < j_zero) {
				move(77); // zero идёт налево
				j_zero--;
			}
		}
		if (i_needed != i_zero) {
			if (i_needed > i_zero) {
				move(72); // zero идёт вниз
				i_zero++;
			}
			else if (i_needed < i_zero) {
				move(80); // zero идёт вверх
				i_zero--;
			}
		}
	}
}

void Board::print() {
	for (int j = 0; j < size; j++)
		std::cout << " ---- ";
	std::cout << std::endl;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++) {
			std::cout << "| ";
			std::cout << __cells[i][j];
			//std::cout << " " << i << " " << j;
			std::cout << " |";
		}
		std::cout << std::endl;
		for (int j = 0; j < size; j++)
			std::cout << " ---- ";
		std::cout << std::endl;
	}
}


void Board::move(int dir) {
	if (dir != 224) {
		int i_zero = 0, j_zero = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (__cells[i][j].get_value() == 0) {
					i_zero = i;
					j_zero = j;
				}
			}
		}
		if (dir == 72 && i_zero < size - 1) { // снизу вверх
			Cell buf = __cells[i_zero][j_zero];
			__cells[i_zero][j_zero] = __cells[i_zero + 1][j_zero];
			__cells[i_zero + 1][j_zero] = buf;
		}
		if (dir == 80 && i_zero > 0) { // сверху вниз
			Cell buf = __cells[i_zero][j_zero];
			__cells[i_zero][j_zero] = __cells[i_zero - 1][j_zero];
			__cells[i_zero - 1][j_zero] = buf;
		}
		if (dir == 75 && j_zero < size - 1) { // слева направо
			Cell buf = __cells[i_zero][j_zero];
			__cells[i_zero][j_zero] = __cells[i_zero][j_zero + 1];
			__cells[i_zero][j_zero + 1] = buf;
		}
		if (dir == 77 && j_zero > 0) { // справа налево
			Cell buf = __cells[i_zero][j_zero];
			__cells[i_zero][j_zero] = __cells[i_zero][j_zero - 1];
			__cells[i_zero][j_zero - 1] = buf;
		}
	}
}

bool Board::victory()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (__cells[i][j].get_value() == 0) {
				if (i != size - 1 || j != size - 1)
					return false;
			}
			else {
				if (__cells[i][j].get_value() != i * size + j + 1)
					return false;
			}
		}
	}
	return true;
}

void Board::restart(){
	shake();
}