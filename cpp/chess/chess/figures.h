#pragma once

#include "board.h"
#include <vector>
#include <iostream>


using namespace std;

class Board;
class Figure;

struct Cell {
	int x, y;
	Figure* fig;
	Cell(int ax, int ay, Figure* afig) : x(ax), y(ay), fig(afig) {};
	Cell() : x(-1), y(-1) {};
};

struct Move {
	Cell src, dst;
	Move() : src(), dst() {};
	Move& operator = (const Move& amove) {
		src = amove.src;
		dst = amove.dst;
		return *this;
	}

	Move changeDstX(int dx) {
		Move new_move = Move(*this);
		new_move.dst.x += dx;
		return new_move;
	}

	Move changeDstY(int dy) {
		Move new_move = Move(*this);
		new_move.dst.y += dy;
		return new_move;
	}

	Move changeDstXY(int dx, int dy) {
		Move new_move = Move(*this).changeDstX(dx);
		return new_move.changeDstY(dy);
	}
};


class Figure {
protected:
	Cell pos;
	virtual vector<Move>* getMovesArray(const Board& board) = 0;
	friend struct Cell;
friend 
};


class King : public Figure {
public:
	vector<Move>* getMovesArray(const Board& board);
};

class Rook : public Figure {

};

class Queen : public Figure {

};

class Pawn : public Figure {

};

class Horse : public Figure {

};

class Elephant : public Figure {

};
