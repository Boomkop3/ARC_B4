//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState state;
    //b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(1, 1);
	BoardPos bp2 = BoardPos(5, 5);
	state.addPieceToPosition(1, 1, Piece::White, true);
	//state.addPieceToPosition(3, 3, Piece::Black, false);
	
	state.printBoard();
	//state.whiteToMove = false;
	bool check = h.checkIfLegalMove(bp, bp2, state);
	//h.checkIfLegalMove(bp, bp2, state);
}

