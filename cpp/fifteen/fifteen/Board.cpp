#include "Board.h"
#include <iostream>
#include <iomanip>

Board::Board() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			__cells[i][j].set_value(i * 4 + j);
		}
	}
}

void Board::print() {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++) {
			std::cout << "| ";
			std::cout << std::setw(2);
			std::cout << __cells[i][j].get_value();
			//std::cout << " " << i << " " << j;
			std::cout << " |";
		}
		std::cout << std::endl;
	}
}


void Board::move(int dir) {
	if (dir != 224) {
		int i_zero = 0, j_zero = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (__cells[i][j].get_value() == 0) {
					i_zero = i;
					j_zero = j;
				}
			}
		}
		//std::cout << i_zero << " " << j_zero << std::endl;
	if (dir == 72 && i_zero < 3) { // снизу вверх
		Cell buf = __cells[i_zero][j_zero];
		__cells[i_zero][j_zero] = __cells[i_zero + 1][j_zero];
		__cells[i_zero + 1][j_zero] = buf;
	}
	if (dir == 80 && i_zero > 0) { // сверху вниз
		Cell buf = __cells[i_zero][j_zero];
		__cells[i_zero][j_zero] = __cells[i_zero - 1][j_zero];
		__cells[i_zero - 1][j_zero] = buf;
	}
	if (dir == 75 && j_zero < 3) { // слева на право
		Cell buf = __cells[i_zero][j_zero];
		__cells[i_zero][j_zero] = __cells[i_zero][j_zero + 1];
		__cells[i_zero][j_zero + 1] = buf;
	}
	if (dir == 77 && j_zero > 0) { // справа на лево
		Cell buf = __cells[i_zero][j_zero];
		__cells[i_zero][j_zero] = __cells[i_zero][j_zero - 1];
		__cells[i_zero][j_zero - 1] = buf;
	}
	
		//if (dir == 72 && i_zero < 9) { // снизу вверх

		//	std::cout << __cells[i_zero + 1][j_zero].get_value() << std::endl;
		//	std::cout << i_zero + 1 << " " << j_zero << std::endl;
		//}
		//if (dir == 80 && i_zero > 0) { // сверху вниз
		//	std::cout << __cells[i_zero - 1][j_zero].get_value() << std::endl;
		//	std::cout << i_zero - 1 << " " << j_zero << std::endl;
		//}
		//if (dir == 75 && j_zero < 9) { // слева на право
		//	std::cout << __cells[i_zero][j_zero + 1].get_value() << std::endl;
		//	std::cout << i_zero << " " << j_zero + 1 << std::endl;
		//}
		//if (dir == 77 && j_zero > 0) { // справа на лево
		//	std::cout << __cells[i_zero][j_zero - 1].get_value() << std::endl;
		//	std::cout << i_zero << " " << j_zero - 1 << std::endl;
		//}
	}
}
