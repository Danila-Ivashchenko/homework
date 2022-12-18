#include "figures.h"

using namespace std;

vector<Move>* King::getMovesArray(const Board& board) {
	vector<Move>* pResult = new vector<Move>(8);
	Move move;
	move.src = pos;
	move.dst = pos;
	if (pos.x >= 1) {
		pResult->push_back(move.changeDstX(-1));
		if (pos.x >= 1) {
			pResult->push_back(move.changeDstXY(-1, -1));
		}
		if (pos.x < 7) {
			pResult->push_back(move.changeDstXY(-1, 1));
		}
	}
	if (pos.x < 7) {
		pResult->push_back(move.changeDstX(1));
		if (pos.x >= 1) {
			pResult->push_back(move.changeDstXY(1, -1));
		}
		if (pos.x < 7) {
			pResult->push_back(move.changeDstXY(1, 1));
		}
	}
	if (pos.x >= 1) {
		pResult->push_back(move.changeDstY(-1));
	}
	if (pos.x < 7) {
		pResult->push_back(move.changeDstY(1));
	}

	return pResult;
}