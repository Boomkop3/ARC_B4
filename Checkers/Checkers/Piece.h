#pragma once
#include "BoardPos.h"
static int id_counter = 0;

class Piece
{
	
public:
	//attributes
	enum PieceColor {White, Black};
	PieceColor color;
	BoardPos position;
	bool isDoublePiece;
	int id;

	//functions
	Piece(PieceColor pieceColor, BoardPos boardPosition);
	void makeDoublePiece();
	bool getIsDoublePiece();
	void updatePosition(BoardPos boardpos);
	void updatePosition(int x, int y);
};

