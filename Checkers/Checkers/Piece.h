#pragma once
#include "BoardPos.h"
class Piece
{
public:
	//attributes
	enum PieceColor {White, Black};
	PieceColor color;
	BoardPos position;
	bool isDoublePiece;
	//functions
	Piece(PieceColor pieceColor, BoardPos boardPosition);
	void makeDoublePiece();
};

