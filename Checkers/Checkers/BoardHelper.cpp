#include "BoardHelper.h"

void BoardHelper::RemovePiece(BoardPos& position, BoardState& state)
{
	//remove piece logic
	int count = 0;
	std::vector<Piece> tempPieces = state.getPieces();
	for (Piece p : tempPieces) {
		if ((p.position.getX() == position.getX()) && (p.position.getY() == position.getY()))
		{
			tempPieces.erase(tempPieces.begin() + count);
			
			state.setPieces(tempPieces);
			state.updatePiecesOnBoardPositions();
			std::cout << "Piece removed at: (" << p.position.getX() << ", " << p.position.getY() << ")" << std::endl;
			return;
		}
		count++;
	}
	std::cout << "no piece found to remove" << std::endl;
}

void BoardHelper::MakeDoublePiece(BoardPos& position, BoardState& state)
{
	//make double piece logic
}

bool BoardHelper::checkIfLegalMove(BoardPos& originalPos, std::vector<BoardPos>& movePositions)
{
	//check if move is legal
	return false;
}
