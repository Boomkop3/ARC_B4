#include "Piece.h"


Piece::Piece(PieceColor pieceColor, BoardPos boardPosition)
{
	color = pieceColor;
	position = boardPosition;
	isDoublePiece = false;
	id = id_counter++;
}

void Piece::makeDoublePiece()
{
	isDoublePiece = true;
}

bool Piece::getIsDoublePiece()
{
	return isDoublePiece;
}

void Piece::updatePosition(BoardPos boardpos) {
	position = boardpos;
}

void Piece::updatePosition(int x, int y) {
	position = BoardPos(x,y);
}

