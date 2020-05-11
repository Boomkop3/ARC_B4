//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState b;
    //b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(0, 0);
    h.MakeDoublePiece(bp, b);    
    b.printBoard();
    h.RemovePiece(bp, b);
    b.printBoard();
}

