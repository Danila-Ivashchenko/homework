#pragma once


#include <map>
#include "figures.h"

using namespace std;

//struct Cell {
//	Figure* figure;
//	void moveFigure();
//	Cell() : figure(0) {};
//	void setFigure(Figure* nfigure) { figure = nfigure; };
//	Figure* getFigure() { return figure; };
//};

//class Board {
//	Cell** cells;
//public:
//	Board() {
//		cells = new Cell * [8];
//		for (int i = 0; i < 8; i++) {
//			cells[i] = new Cell[8];
//		}
//	}
//
//};


class Figure;
struct Cell;

class Board {
	map <Cell, Figure*> pFigures;

public:
	void fillBoard();
	friend class Figure;
};
