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
	//if(obligatedToTake(state)){
	//	//check if move being played actually takes a piece.
	//	
	//}
	
	if (checkForCorrectNormalMove(originalPos, movePosition, state))
	{
		//check if moved piece is yours
		//check if destination is not occupied
		//check if move is not a bs move
		return true;
	}
	

	//check if move is legal
	return false;
}

bool BoardHelper::checkForCorrectNormalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state))
	{
		if (checkIfLegalNormalMove(originalPos, movePosition, state)) {
			return true;
		}
	}
	return false;
}

bool BoardHelper::checkIfPieceToMoveIsCorrectColor(BoardPos& originalPos, BoardState& state) {
	Piece::PieceColor colorToMove = Piece::Black;
	if (state.whiteToMove)
	{
		colorToMove = Piece::White;
	}

	if (state.getSingleBoardPos(originalPos.getX(), originalPos.getY())->checkOccupied()) {
		if (state.getSinglePiece(originalPos.getX(), originalPos.getY())->color == colorToMove) {
			return true;
		}
	}
	return false;
}

bool BoardHelper::checkIfDestinationIsEmpty(BoardPos& movePosition, BoardState& state) {
	return !(state.getSingleBoardPos(movePosition.getX(), movePosition.getY())->checkOccupied());
}

bool BoardHelper::checkIfLegalNormalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	if (state.whiteToMove)
	{
		// left move
		if ((originalPos.getX() - 1) == movePosition.getX() && (originalPos.getY() + 1) == movePosition.getY())
		{
			return true;
		}

		// right move
		if ((originalPos.getX() + 1) == movePosition.getX() && (originalPos.getY() + 1) == movePosition.getY())
		{
			return true;
		}
	}
	else {
		// left move
		if ((originalPos.getX() - 1) == movePosition.getX() && (originalPos.getY() - 1) == movePosition.getY())
		{
			return true;
		}

		// right move
		if ((originalPos.getX() + 1) == movePosition.getX() && (originalPos.getY() - 1) == movePosition.getY())
		{
			return true;
		}
	}
	return false;
}

bool BoardHelper::obligatedToTake(BoardState& state) {
	std::vector<Piece> currentPieces = getCurrentlyUsedPieces(state);
	
	for (Piece piece : currentPieces) {
		if (checkIfPieceCanTake(piece, state)) {
			if (piece.color == 0) {
				std::cout << "white must take a piece" << std::endl;
			}
			else {
				std::cout << "black must take a piece" << std::endl;
			}		
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