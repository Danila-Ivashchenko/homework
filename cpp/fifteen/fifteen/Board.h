#pragma once
#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

class Cell;
class Board;


struct Coords {
	int i = 0;
	int j = 0;
	Coords(int ai, int aj) : i(ai), j(aj) {};
};

class Cell {
	int __value;
	int __x, __y;
public:
	Cell() : __value(0), __x(0), __y(0) {};
	Cell(int value, int x, int y) : __value(value), __x(x), __y(y) {};
	int get_value() { return __value; };
	int x() { return __x; };
	int y() { return __y; };
	void set_value(int value) { __value = value; };
	void set_coords(int x, int y) { __x = x; __y = y; };
friend std::ostream& operator << (std::ostream& out, Cell & cell);
};


class Board {
	int size = 4;
	Cell** __cells = new Cell*[size];
	void move_zero_cell(int i_needed, int j_needed);
public:
	Board();
	//~Board();
	Board(const Board& other);
	void shake();
	void move(int dir);
	bool victory();
	void print();
	void restart();
	int get_size() { return size; };
	Cell** get_cells() { return __cells; };
	Coords find_zero();
};
