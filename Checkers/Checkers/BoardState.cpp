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
			pieces.push_back(Piece(Piece::White, *getSingleBoardPos(0, i)));
		}
	}
	//rij 2
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			pieces.push_back(Piece(Piece::White, *getSingleBoardPos(1, i)));
		}
	}
	//rij 3
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 == 0) {
			pieces.push_back(Piece(Piece::White, *getSingleBoardPos(2, i)));
		}
	}

	// rij 6
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			pieces.push_back(Piece(Piece::Black, *getSingleBoardPos(5, i)));
		}
	}
	// rij 7
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 == 0) {
			pieces.push_back(Piece(Piece::Black, *getSingleBoardPos(6, i)));
		}
	}
	// rij 8
	for (int i = 0; i < boardSize; i++)
	{
		if (i % 2 != 0) {
			pieces.push_back(Piece(Piece::Black, *getSingleBoardPos(7, i)));
		}
	}

	//test!!!! haal deze weg !!!!
	pieces.push_back(Piece(Piece::White, *getSingleBoardPos(4, 6)));
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


