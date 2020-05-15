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
	std::vector<Piece> tempPieces = state.getPieces();
	int count = 0;
	for (Piece p : tempPieces) {
		if ((p.position.getX() == position.getX()) && (p.position.getY() == position.getY()))
		{
			p.makeDoublePiece();
			tempPieces.push_back(p);
			tempPieces.erase(tempPieces.begin() + count);
			state.setPieces(tempPieces);
			state.updatePiecesOnBoardPositions();
			return;
		}
		count++;
	}
}

bool BoardHelper::checkIfLegalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state)
{
	if(obligatedToTake(originalPos,movePosition,state)){
		//check if move being played actually takes a piece.
		
	}
	//check if move is legal
	return false;
}

bool BoardHelper::obligatedToTake(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	std::vector<Piece> currentPieces = getCurrentlyUsedPieces(state);
	
	for (Piece piece : currentPieces) {
		if (checkIfPieceCanTake(piece, state)) {
			return true;
		}
	}
	return false;
}

std::vector<Piece> BoardHelper::getCurrentlyUsedPieces(BoardState& state) {
	bool whiteToMove = state.whiteToMove;
	std::vector<Piece> currentPieces;
	for (Piece piece : state.getPieces()) {
		if (piece.color == piece.White && whiteToMove) {
			currentPieces.push_back(piece);
		}
		else if (piece.color == piece.Black && !whiteToMove) {
			currentPieces.push_back(piece);
		}
	}
	return currentPieces;
}

bool BoardHelper::checkIfPieceCanTake(Piece piece, BoardState& state) {

	if (checkLeftUp(piece,state) || checkLeftDown(piece, state) || checkRightDown(piece, state) || checkRightUp(piece, state)) {
		return true;
	}
	else {
		return false;
	}

}

bool BoardHelper::checkLeftUp(Piece piece, BoardState& state) {
	//left up
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck = x - 1;
	int yToCheck = y - 1;
	try {
		BoardPos* currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (Piece currentPiece : state.getPieces()) {
				if (currentPiece.position.getX() == currentPos->getX() && currentPiece.position.getY() == currentPos->getY() && currentPiece.color != piece.color) {
					xToCheck -= 1;
					yToCheck -= 1;
					currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
					if (!(currentPos->checkOccupied())) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::out_of_range& e) {
		//empty catch to continue with other checks
		return false;
	}
	return false;
}

bool BoardHelper::checkRightUp(Piece piece, BoardState& state) {

	//right up
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck = x + 1;
	int yToCheck = y - 1;

	try {
		BoardPos* currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (Piece currentPiece : state.getPieces()) {
				if (currentPiece.position.getX() == currentPos->getX() && currentPiece.position.getY() == currentPos->getY() && currentPiece.color != piece.color) {
					xToCheck += 1;
					yToCheck -= 1;
					currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
					if (!(currentPos->checkOccupied())) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::out_of_range& e) {
		//empty catch to continue with other checks
		return false;
	}
	return false;
}

bool BoardHelper::checkLeftDown(Piece piece, BoardState& state) {
	//left down
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck = x - 1;
	int yToCheck = y + 1;
	try {
		BoardPos* currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (Piece currentPiece : state.getPieces()) {
				if (currentPiece.position.getX() == currentPos->getX() && currentPiece.position.getY() == currentPos->getY() && currentPiece.color != piece.color) {
					xToCheck -= 1;
					yToCheck += 1;
					currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
					if (!(currentPos->checkOccupied())) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::out_of_range& e) {
		//empty catch to continue with other checks
		return false;
	}
	return false;
}

bool BoardHelper::checkRightDown(Piece piece, BoardState& state) {

	//right down
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck = x + 1;
	int yToCheck = y + 1;
	try {
		BoardPos* currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (Piece currentPiece : state.getPieces()) {
				if (currentPiece.position.getX() == currentPos->getX() && currentPiece.position.getY() == currentPos->getY() && currentPiece.color != piece.color) {
					xToCheck += 1;
					yToCheck += 1;
					currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
					if (!(currentPos->checkOccupied())) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::out_of_range& e) {
		//empty catch to continue with other checks
		return false;
	}
	return false;
}