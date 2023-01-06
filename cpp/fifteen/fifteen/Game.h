#pragma once
#include "Board.h"
#include "Viewer.h"

class Game {
	Board* __board;
	Viewer viewer;
	int __status; // 0 - ������ ����, 1 - �������� ����, 2 - ���� �������� � ������� ��������, 3 - �����, 5 - �����
public:
	Game(Board* board) : __board(board), __status(0) {};
	void engine();
	void render();
	void start();
	void play();
	void menu();
	void restart();
	void exit();
};