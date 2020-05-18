//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState state;
    //b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(0, 0);
	BoardPos bp2 = BoardPos(5, 7);
	state.printBoard();
	 bool check = h.obligatedToTake(state);
	//h.checkIfLegalMove(bp, bp2, state);
}

