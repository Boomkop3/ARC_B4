#include "Piece.h"


Piece::Piece(PieceColor pieceColor, BoardPos boardPosition)
{
	color = pieceColor;
	position = boardPosition;
	isDoublePiece = false;
}

void Piece::makeDoublePiece()
{
	isDoublePiece = true;
}
