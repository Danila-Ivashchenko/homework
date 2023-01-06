#include "Viewer.h"


void Viewer::print_starting_label(){
	std::cout << "����� ���������� � ���� 15\n";
	std::cout << "��� ������ ���� ������� \"Enter\"\n";
}

void Viewer::print_menu() {
	std::cout << "��� ����������� �������� �� ������ ����� ����������� ���������" << std::endl;
	std::cout << "��� ������ �� ���� ������� \"Esc\"" << std::endl;
	std::cout << "��� ������� ���������� ����� ������� \"h\"" << std::endl;
	std::cout << "��� ������ �� ���� ������� \"m\"" << std::endl;
	//std::cout << "��� ��������� ����" << std::endl;
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
	std::cout << "��� �������� ���� ������� \"m\"\n";
}


void Viewer::print_victory() {
	std::cout << "����������, �� ��������!!!\n������� \"Enter\" ��� �����������\n";
}

void Viewer::print_exit() {
	std::cout << "������� \"Enter\" ��� ������ �� ����";
}