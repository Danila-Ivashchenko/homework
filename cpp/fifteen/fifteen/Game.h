#pragma once
#include "Board.h"
#include "Viewer.h"
#include "Bot.h"

class Game {
	Board* __board;
	Viewer viewer;
	Bot __bot;
	int __status; // 0 - ������ ����, 1 - �������� ����, 2 - ���� �������� � ������� ��������, 3 - �����, 4 - ������ ���, 5 - �����
public:
	Game(Board* board) : __board(board), __status(0), __bot(*board) {};
	void engine();
	void render();
	void start();
	void play();
	void menu();
	void restart();
	void bot_mod();
	void exit();
};