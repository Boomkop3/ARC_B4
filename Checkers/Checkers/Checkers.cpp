//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState state;
	state.whiteToMove = false;
    //b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(1, 5);
	BoardPos bp2 = BoardPos(0, 4);
	state.printBoard();
	//state.whiteToMove = false;
	bool check = h.checkIfLegalMove(bp, bp2, state);
	//h.checkIfLegalMove(bp, bp2, state);
}

