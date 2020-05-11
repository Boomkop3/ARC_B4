//#include "BoardState.h"
#include "BoardHelper.h"
#include <iostream>

int main()
{
    BoardState b;
    b.printBoard();
    BoardHelper h;
    BoardPos bp = BoardPos(0, 0);
    h.RemovePiece(bp, b);
    bp = BoardPos(2, 1);
    h.RemovePiece(bp, b);
    bp = BoardPos(2, 2);
    h.RemovePiece(bp, b);
    bp = BoardPos(7, 7);
    h.RemovePiece(bp, b);
    b.printBoard();
}

