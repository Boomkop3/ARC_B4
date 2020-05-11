#include "BoardPos.h"
#include "Piece.h"
#include <vector>
#include <iostream>


class BoardState
{
public:
	//constructor
	BoardState();
	//functions
	std::vector<std::vector<BoardPos>> getBoardPositions();
	std::vector<Piece> getPieces();
	void setPieces(std::vector<Piece> _pieces);
	void updatePiecesOnBoardPositions();

	void printBoard();
private:
	//attributes
	const int boardSize = 8;
	std::vector<std::vector<BoardPos>> boardPositions;
	std::vector<Piece> pieces;

	//functions
	void initializeBoardPositions();
	void placeStartPieces();
	
	BoardPos* getSingleBoardPos(int x, int y);
	
};

