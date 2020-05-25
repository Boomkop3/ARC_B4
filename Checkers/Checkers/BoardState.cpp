#include "BoardState.h"

BoardState::BoardState()
{
	//initialize board positions
	initializeBoardPositions();

	//add pieces to board
	placeStartPieces();
	updatePiecesOnBoardPositions();
}

std::vector<std::vector<BoardPos>> BoardState::getBoardPositions()
{
	return boardPositions;
}

std::vector<Piece> BoardState::getPieces()
{
	return pieces;
}

void BoardState::setPieces(std::vector<Piece> _pieces)
{
	pieces = _pieces;
}

void BoardState::initializeBoardPositions()
{
	for (int y = 0; y < boardSize; y++)
	{
		std::vector<BoardPos> row;
		for (int x = 0; x < boardSize; x++)
		{
			row.push_back(BoardPos(y, x));		
		}
		boardPositions.push_back(row);
	}
}

//zet opzet van zwarte en witte stukken aan het begin van het spel
void BoardState::placeStartPieces()
{
	//rij 1
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 == 0) {
			addPieceToPosition(i, 0, Piece::White, false);
		}
	}
	//rij 2
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			addPieceToPosition(i, 1, Piece::White, false);
		}
	}
	//rij 3
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 == 0) {
			addPieceToPosition(i, 2, Piece::White, false);
		}
	}

	// rij 6
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			addPieceToPosition(i, 5, Piece::Black, false);
		}
	}
	// rij 7
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 == 0) {
			addPieceToPosition(i, 6, Piece::Black, false);
		}
	}
	// rij 8
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			addPieceToPosition(i, 7, Piece::Black, false);
		}
	}
}

void BoardState::addPieceToPosition(int x, int y, Piece::PieceColor color, bool isDouble) {
	Piece p(color, *getSingleBoardPos(x, y));
	if (isDouble)
	{
		p.makeDoublePiece();
	}
	pieces.push_back(p);
	updatePiecesOnBoardPositions();
}

void BoardState::updatePiecesOnBoardPositions()
{
	//door pieces loopen
	//plek van pieces als isOccupied zetten

	for (std::vector<BoardPos> t : getBoardPositions())
	{
		for (BoardPos pos : t)
		{
			pos.setOccupied(false);
		}
	}

	

	for (Piece p : pieces)
	{
		getSingleBoardPos(p.position.getX(), p.position.getY())->setOccupied(true);
	}

}

BoardPos* BoardState::getSingleBoardPos(int x, int y)
{
	return &boardPositions.at(x).at(y);
}

Piece* BoardState::getSinglePiece(int xPos, int yPos) {
	for (Piece p : pieces) {
		if (p.position.getX() == xPos && p.position.getY() == yPos)
		{
			return &p;
		}
	}
	return nullptr;
}

void BoardState::printBoard()
{
	char board[64] = { ' ' };

	for (Piece p : pieces)
	{
		int pos2d = (p.position.getY() * 8) + p.position.getX();
		if (p.color == Piece::Black)
		{
			if (p.getIsDoublePiece())
			{
				board[pos2d] = 'B';
			}
			else {
				board[pos2d] = 'b';
			}
			
		}
		else {
			if (p.getIsDoublePiece()) {
				board[pos2d] = 'W';
			}
			else {
				board[pos2d] = 'w';
			}
			
		}
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++) {
			std::cout << board[y * 8 + x];
		}
		std::cout << std::endl;
	}
}

bool BoardState::checkGameFinished()
{
	return false;
}


