#include "BoardState.h"

BoardState::BoardState()
{
	boardPositions = std::make_shared<std::vector<std::vector<std::shared_ptr<BoardPos>>>>();
	pieces = std::make_shared<std::vector<std::shared_ptr<Piece>>>();

	//initialize board positions
	initializeBoardPositions();

	//add pieces to board
	//placeStartPieces();
	updatePiecesOnBoardPositions();
}

void BoardState::updateBoard() {
	//do all updates
	updatePiecesOnBoardPositions();
	if (checkGameFinished()) {
		gameFinished = true;
	}
}

std::shared_ptr<std::vector<std::vector<std::shared_ptr<BoardPos>>>> BoardState::getBoardPositions()
{
	return boardPositions;
}

std::shared_ptr<std::vector<std::shared_ptr<Piece>>> BoardState::getPieces()
{
	return pieces;
}

void BoardState::setPieces(std::shared_ptr<std::vector<std::shared_ptr<Piece>>> _pieces)
{
	pieces = _pieces;
}

void BoardState::initializeBoardPositions()
{
	for (int y = 0; y < boardSize; y++)
	{
		std::vector<std::shared_ptr<BoardPos>> row;
		for (int x = 0; x < boardSize; x++)
		{
			row.push_back(std::make_shared<BoardPos>(y, x));		
		}
		boardPositions->push_back(row);
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
	std::shared_ptr<Piece> p = std::make_shared<Piece>(color, getSingleBoardPos(x, y));
	if (isDouble)
	{
		p->makeDoublePiece();
	}
	pieces->push_back(p);
	updatePiecesOnBoardPositions();
}

void BoardState::updatePiecesOnBoardPositions()
{
	//door pieces loopen
	//plek van pieces als isOccupied zetten

	for (std::vector<std::shared_ptr<BoardPos>> t : *getBoardPositions())
	{
		for (std::shared_ptr<BoardPos> pos : t)
		{
			pos->setOccupied(false);
		}
	}

	for (std::shared_ptr<Piece> p : *pieces)
	{
		getSingleBoardPos(p->position->getX(), p->position->getY())->setOccupied(true);
	}

}

std::shared_ptr<BoardPos> BoardState::getSingleBoardPos(int x, int y)
{
	return boardPositions->at(x).at(y);
}

std::shared_ptr<Piece> BoardState::getSinglePiece(int xPos, int yPos) {
	for (std::shared_ptr<Piece> p : *pieces) {
		if (p->position->getX() == xPos && p->position->getY() == yPos)
		{
			return p;
		}
	}
	return nullptr;
}

std::shared_ptr<Piece> BoardState::getSinglePiece(std::shared_ptr<BoardPos> boardPos) {
	for (std::shared_ptr<Piece> p : *pieces) {
		if (p->position->getX() == boardPos->getX() && p->position->getY() == boardPos->getY())
		{
			return p;
		}
	}
	return nullptr;
}


void BoardState::printBoard()
{
	char board[64] = { ' ' };

	for (std::shared_ptr<Piece> p : *pieces)
	{
		int pos2d = (p->position->getY() * 8) + p->position->getX();
		if (p->color == Piece::Black)
		{
			if (p->getIsDoublePiece())
			{
				board[pos2d] = 'B';
			}
			else {
				board[pos2d] = 'b';
			}
			
		}
		else {
			if (p->getIsDoublePiece()) {
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
	int whiteCount = 0;
	int blackCount = 0;
	for(std::shared_ptr<Piece> piece : *pieces)
	{
		if (whiteCount > 0 && blackCount > 0) {
			return false;
		}
		if (piece->color == Piece::White) {
			whiteCount++;
		}
		else if (piece->color == Piece::Black) {
			blackCount++;
		}
	}
	if (whiteCount == 0 || blackCount == 0) {
		//game has ended if one of the sides does not have pieces left
		return true;
	}
	return false;
}

int BoardState::getBoardSize()
{
	return boardSize;
}

void BoardState::swapTurn() {
	whiteToMove = !whiteToMove;
	std::cout << "white to move: " << whiteToMove << std::endl;
}


