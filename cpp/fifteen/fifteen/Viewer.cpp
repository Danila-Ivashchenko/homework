#include "Viewer.h"


void Viewer::print_starting_label(){
	std::cout << "Добро пожаловать в игру 15\n";
	std::cout << "Для начала игры нажмите \"Enter\"\n";
}

void Viewer::print_menu() {
	std::cout << "Для перемещения костяшек на пустое место используйте стрелочки" << std::endl;
	std::cout << "Для выхода из игры нажмите \"Esc\"" << std::endl;
	std::cout << "Для решения головолмки ботом нажмите \"h\"" << std::endl;
	std::cout << "Для выхода из меню нажмите \"m\"" << std::endl;
	//std::cout << "Для прочтения прав" << std::endl;
}

void Viewer::clear_window(){
	system("cls");
}

int Viewer::get_key() {
	int code = _getch();
	if (code == 224)
		code = _getch();
	return code;
}

void Viewer::print_board(Cell** arr){
	int size = 4;
	for (int j = 0; j < size; j++)
		std::cout << " ---- ";
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << "| ";
			std::cout << arr[i][j];
			//std::cout << " " << i << " " << j;
			std::cout << " |";
		}
		std::cout << std::endl;
		for (int j = 0; j < size; j++)
			std::cout << " ---- ";
		std::cout << std::endl;
	}
	std::cout << "для открытия меню нажмите \"m\"\n";
}


void Viewer::print_victory() {
	std::cout << "Поздравляю, вы победили!!!\nНажмите \"Enter\" для продолжения\n";
}

void Viewer::print_exit() {
	std::cout << "Нажмите \"Enter\" для выхода их игры";
}