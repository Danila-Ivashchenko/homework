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

void Board::shake()
{
	srand((unsigned)time(0));
	int moves[4] = {72, 75, 77, 80}; 

	for (int i = 0; i < size * size * size; i++)
		move(moves[rand() % 4]);
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