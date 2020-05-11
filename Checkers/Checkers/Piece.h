#pragma once
#include "BoardPos.h"
class Piece
{
	bool isDoublePiece;
public:
	//attributes
	enum PieceColor {White, Black};
	PieceColor color;
	BoardPos position;
	
	//functions
	Piece(PieceColor pieceColor, BoardPos boardPosition);
	void makeDoublePiece();
	bool getIsDoublePiece();


};

