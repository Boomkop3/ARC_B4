#include "BoardPos.h"
#include "Piece.h"
#include <vector>
#include <iostream>


class BoardState
{
public:
	//constructor
	BoardState();
	void updateBoard();
	//functions
	std::shared_ptr<std::vector<std::vector<std::shared_ptr<BoardPos>>>> getBoardPositions();
	std::shared_ptr<std::vector<std::shared_ptr<Piece>>> getPieces();
	void setPieces(std::shared_ptr<std::vector<std::shared_ptr<Piece>>> _pieces);
	void updatePiecesOnBoardPositions();
	void printBoard();
	bool checkGameFinished();

	int getBoardSize();

	void swapTurn();

	void addPieceToPosition(int x, int y, Piece::PieceColor, bool isDouble);

	std::shared_ptr<BoardPos> getSingleBoardPos(int x, int y);

	std::shared_ptr<Piece> getSinglePiece(int xPos, int yPos);

	std::shared_ptr<Piece> getSinglePiece(std::shared_ptr<BoardPos> boardPos);

	//attributes
	bool whiteToMove = true;
	bool gameFinished;
private:
	//attributes
	const int boardSize = 8;
	std::shared_ptr<std::vector<std::vector<std::shared_ptr<BoardPos>>>> boardPositions;
	std::shared_ptr<std::vector<std::shared_ptr<Piece>>> pieces;
	
	//functions
	void initializeBoardPositions();
	void placeStartPieces();

	
	
	
	
};

