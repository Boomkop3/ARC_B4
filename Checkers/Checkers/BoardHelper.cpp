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

BoardHelper::checkerstate BoardHelper::makeMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	
	if (checkIfLegalMove(originalPos, movePosition, state)) {
		//make move on board
		

		//promote piece if allowed
		Piece& piece = *(state.getSinglePiece(originalPos));
		if (checkIfPieceCanPromote(piece)) {
			piece.makeDoublePiece();
		}

		//check if game has ended
		if (state.checkGameFinished()) {
			return  BoardHelper::checkerstate::GAMECOMPLETED;
		}

		//end of player's turn
		state.swapTurn();
		return BoardHelper::checkerstate::VALIDMOVE;
	}
	else {
		//dont make move on board
		return BoardHelper::checkerstate::INVALIDMOVE;
	}
}

bool BoardHelper::checkIfLegalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state)
{
	if (state.getSinglePiece(originalPos.getX(), originalPos.getY()) == nullptr)
	{
		return false;
	}

	if(obligatedToTake(state)){
		//check if position to move to is not already occupied
		if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state)) {
			//check if move being played actually takes a piece.
			if (state.getSingleBoardPos(originalPos.getX(), originalPos.getY())->checkOccupied()) {
				if (checkIfPieceCanTake(*(state.getSinglePiece(originalPos)), state)) {
					return true;
				}
			}
		}
		
		
		return false;
	}
	
		if(!(state.getSinglePiece(originalPos.getX(), originalPos.getY())->getIsDoublePiece())) {
			if (checkForCorrectNormalMove(originalPos, movePosition, state))
			{
				return true;
			}
		}
		else {
			if (checkForCorrectDoublePieceMove(originalPos, movePosition, state))
			{
				return true;
			}
		}
	
	return false;
}

bool BoardHelper::checkForCorrectDoublePieceMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state))
	{
		if (checkIfLegalDoublePieceMove(originalPos, movePosition, state))
		{
			return true;
		}
	}
	return false;
}

bool BoardHelper::checkIfLegalDoublePieceMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	//check if every pos the piece moves over is not occupied
	
	int deltaXpos = movePosition.getX() - originalPos.getX();
	int deltaYpos = movePosition.getY() - originalPos.getY();

	if (deltaXpos == 0 || deltaYpos == 0)
	{
		return false;
	}

	int x = originalPos.getX();
	int y = originalPos.getY();

	//left up
	if (deltaXpos < 0 && deltaYpos < 0)
	{
		for (int i = 0; i < abs(deltaXpos) - 1; i++)
		{
			x -= 1;
			y -= 1;
			
			if (state.getSingleBoardPos(x, y)->checkOccupied() && i != abs(deltaXpos) - 2) {
				return false;
			}
			else if (state.getSingleBoardPos(x, y)->checkOccupied() && i == abs(deltaXpos) - 2){
				if (state.getSinglePiece(x, y)->color != state.getSinglePiece(originalPos.getX(), originalPos.getY())->color)
				{
					return true;
				}
				return false;
			}
		}
		return true;
	}

	//left down
	if (deltaXpos < 0 && deltaYpos > 0)
	{
		for (int i = 0; i < abs(deltaXpos) - 1; i++)
		{
			x -= 1;
			y += 1;

			if (state.getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state.getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
				return true;
			}
		}
		return true;
	}

	//right up
	if (deltaXpos > 0 && deltaYpos < 0)
	{
		for (int i = 0; i < abs(deltaXpos) - 1; i++)
		{
			x += 1;
			y -= 1;

			if (state.getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state.getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
				return true;
			}
		}
		return true;
	}

	//right down
	if (deltaXpos > 0 && deltaYpos > 0)
	{
		for (int i = 0; i < abs(deltaXpos) - 1; i++)
		{
			x += 1;
			y += 1;

			if (state.getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state.getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
				return true;
			}
		}
		return true;
	}

	return false;
}

bool BoardHelper::checkForCorrectNormalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state) {
	if (!(state.getSinglePiece(originalPos.getX(), originalPos.getY())->getIsDoublePiece()));
	{
		if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state))
		{
			if (checkIfLegalNormalMove(originalPos, movePosition, state)) {
				return true;
			}
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
	if (!(piece.getIsDoublePiece())) { // single piece
		if (checkDirectionSinglePieceCanTake(piece, state, LEFTUP) || checkDirectionSinglePieceCanTake(piece, state, RIGHTUP) || checkDirectionSinglePieceCanTake(piece, state, LEFTDOWN) || checkDirectionSinglePieceCanTake(piece, state, RIGHTDOWN)) {
			return true;
		}
		else {
			return false;
		}
	}
	else { // double piece
		if (checkDircectionDoublePieceCanTake(piece, state, LEFTUP) || checkDircectionDoublePieceCanTake(piece, state, RIGHTUP) || checkDircectionDoublePieceCanTake(piece, state, LEFTDOWN) || checkDircectionDoublePieceCanTake(piece, state, RIGHTDOWN))
		{
			return true;
		}
		else {
			return false;
		}
		
	}
	

}

bool BoardHelper::checkDircectionDoublePieceCanTake(Piece piece, BoardState& state, BoardHelper::directions direction) {
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck = x;
	int yToCheck = y;
	bool foundOpposingPiece = false;
	

	try {

		for (int i = 0; i < state.getBoardSize(); i++) {
			switch (direction)
			{
			case BoardHelper::LEFTUP:
				xToCheck -= 1;
				yToCheck -= 1;
				break;
			case BoardHelper::RIGHTUP:
				xToCheck += 1;
				yToCheck -= 1;
				break;
			case BoardHelper::LEFTDOWN:
				xToCheck -= 1;
				yToCheck += 1;
				break;
			case BoardHelper::RIGHTDOWN:
				xToCheck += 1;
				yToCheck += 1;
				break;
			default:
				break;
			}

			BoardPos* pos = state.getSingleBoardPos(xToCheck, yToCheck);

			if (pos->checkOccupied())
			{
				if (state.getSinglePiece(pos->getX(), pos->getY())->color == piece.color) {
					return false;
				}
				else {
					if (foundOpposingPiece)
					{
						return false;
					}
					foundOpposingPiece = true;
				}
			}
			else {
				if (foundOpposingPiece)
				{
					return true;

				}
			}
		}

	}
	catch (const std::out_of_range & e) {
		return false;
	}
}

bool BoardHelper::checkDirectionSinglePieceCanTake(Piece piece, BoardState& state, BoardHelper::directions direction) {
	int x = piece.position.getX();
	int y = piece.position.getY();
	int xToCheck, yToCheck;
	switch (direction)
	{
	case BoardHelper::LEFTUP:
		xToCheck = x - 1;
		yToCheck = y - 1;
		break;
	case BoardHelper::RIGHTUP:
		xToCheck = x + 1;
		yToCheck = y - 1;
		break;
	case BoardHelper::LEFTDOWN:
		xToCheck = x - 1;
		yToCheck = y + 1;
		break;
	case BoardHelper::RIGHTDOWN:
		xToCheck = x + 1;
		yToCheck = y + 1;
		break;
	}

	try {
		BoardPos* currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (Piece currentPiece : state.getPieces()) {
				if (currentPiece.position.getX() == currentPos->getX() && currentPiece.position.getY() == currentPos->getY() && currentPiece.color != piece.color) {
					
					switch (direction)
					{
					case BoardHelper::LEFTUP:
						xToCheck -= 1;
						yToCheck -= 1;
						break;
					case BoardHelper::RIGHTUP:
						xToCheck += 1;
						yToCheck -= 1;
						break;
					case BoardHelper::LEFTDOWN:
						xToCheck -= 1;
						yToCheck += 1;
						break;
					case BoardHelper::RIGHTDOWN:
						xToCheck += 1;
						yToCheck += 1;
						break;
					default:
						break;
					}

					currentPos = state.getSingleBoardPos(xToCheck, yToCheck);
					if (!(currentPos->checkOccupied())) {
						return true;
					}
				}
			}
		}
	}
	catch (const std::out_of_range & e) {
		//empty catch to continue with other checks
		return false;
	}
	return false;
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

bool BoardHelper::checkIfPieceCanPromote(Piece piece) {
	if (piece.color == Piece::White && piece.position.getY() == 7) {
		return true;
	}
	else if (piece.color == Piece::Black && piece.position.getY() == 0) {
		return true;
	}

	return false;
}