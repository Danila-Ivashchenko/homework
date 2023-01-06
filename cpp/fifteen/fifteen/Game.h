#pragma once
#include "Board.h"
#include "Viewer.h"
#include "Bot.h"

class Game {
	Board* __board;
	Viewer viewer;
	Bot __bot;
	int __status; // 0 - запуск игры, 1 - активная игра, 2 - игра окончена и ожидает рестарта, 3 - пауза, 4 - играет бот, 5 - выход
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