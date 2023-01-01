#pragma once

class Cell;
class Board;

class Cell {
	int __value;
public:
	Cell() : __value(0) {};
	Cell(int value) : __value(value) {};
	int get_value() { return __value; };
	void set_value(int value) { __value = value; };
};


class Board {
	Cell __cells[4][4];
public:
	Board();
	void shake();
	void move(int dir);
	bool victory();
	void print();
};