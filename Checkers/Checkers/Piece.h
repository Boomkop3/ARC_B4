#pragma once
#include "BoardPos.h"
#include <iostream>
static int id_counter = 0;

class Piece
{
	
public:
	//attributes
	typedef enum PieceColor {White, Black} PieceColor;
	PieceColor color;
	std::shared_ptr<BoardPos> position;
	bool isDoublePiece;
	int id;

	//functions
	Piece(PieceColor pieceColor, std::shared_ptr<BoardPos> boardPosition);
	void makeDoublePiece();
	bool getIsDoublePiece();
	//void updatePosition(BoardPos boardpos);
	void updatePosition(int x, int y);
};

