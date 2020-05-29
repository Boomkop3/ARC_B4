//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState state;
	state.whiteToMove = true;
    //b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(4, 4);
	BoardPos bp2 = BoardPos(1, 1);
	BoardPos bp3 = BoardPos(3, 3);
	BoardPos bp4 = BoardPos(5, 5);
	state.addPieceToPosition(4, 4, Piece::White, true);
	state.addPieceToPosition(2, 2, Piece::Black, false);
	state.addPieceToPosition(5, 5, Piece::Black, false);

	
	state.printBoard();
	//state.whiteToMove = false;
	h.makeMove(bp, bp2, state);

	state.printBoard();

	h.makeMove(bp4, bp3, state); 
	
	state.printBoard();

	//h.checkIfLegalMove(bp, bp2, state);
}

