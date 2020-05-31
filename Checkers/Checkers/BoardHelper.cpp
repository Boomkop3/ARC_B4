#include "BoardHelper.h"

void BoardHelper::RemovePiece(std::shared_ptr<BoardPos> position, std::shared_ptr<BoardState> state)
{
	for (int i = 0; i < state->getPieces()->size(); i++) {
		if (((*state->getPieces())[i]->position->getX() == position->getX()) && ((*state->getPieces())[i]->position->getY() == position->getY()))
		{
			std::cout << "Piece will be removed at: (" << (*state->getPieces())[i]->position->getX() << ", " << (*state->getPieces())[i]->position->getY() << ")" << std::endl;
			std::cout << "Pieces length: " << state->getPieces()->size() << " Current index " << i << std::endl;
			state->getPieces()->erase(state->getPieces()->begin() + i);
			state->updatePiecesOnBoardPositions();
			return;
		}
	}
}

void BoardHelper::MakeDoublePiece(std::shared_ptr<BoardPos> position, std::shared_ptr<BoardState> state)
{
	for (std::shared_ptr<Piece> p : *state->getPieces()) {
		if ((p->position->getX() == position->getX()) && (p->position->getY() == position->getY()))
		{
			p->makeDoublePiece();
			state->updatePiecesOnBoardPositions();
			return;
		}
	}
}

BoardHelper::checkerstate BoardHelper::makeMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	std::shared_ptr<BoardPos> potentialTakePosition = std::make_shared<BoardPos>();

	if (checkIfLegalMove(originalPos, movePosition, state, potentialTakePosition)) {

		//make move if legal
		std::shared_ptr<Piece> piece = state->getSinglePiece(originalPos);
		piece->updatePosition(movePosition->getX(), movePosition->getY());

		//state.getSinglePiece(originalPos)->updatePosition(movePosition);
		std::cout << piece->id << std::endl;
		//remove piece if neccesary
		if (potentialTakePosition->getX() != -1 && potentialTakePosition->getY() != -1) {
			RemovePiece(potentialTakePosition, state);
		}
		//update board with changes
		state->updateBoard();

		//promote piece if allowed
		if (checkIfPieceCanPromote(state->getSinglePiece(movePosition))) { // Was originalPos
			state->getSinglePiece(movePosition)->makeDoublePiece();		   // Was originalPos
		}


		//check if game has ended
		if (state->gameFinished) {
			return  BoardHelper::checkerstate::GAMECOMPLETED;
		}

		//end of player's turn
		state->swapTurn();
		return BoardHelper::checkerstate::VALIDMOVE;
	}
	else {
		//dont make move on board
		return BoardHelper::checkerstate::INVALIDMOVE;
	}
}

bool BoardHelper::checkIfLegalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake)
{
	if (state->getSinglePiece(originalPos->getX(), originalPos->getY()) == nullptr)
	{
		return false;
	}

	if (obligatedToTake(state, positionToTake)) {
		//check if position to move to is not already occupied
		if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state)) {
			//check if move being played actually takes a piece.
			if (state->getSingleBoardPos(originalPos->getX(), originalPos->getY())->checkOccupied()) {
				if (checkIfPieceCanTake(state->getSinglePiece(originalPos), state, positionToTake)) {
					return true;
				}
			}
		}
		return false;
	}

	if (!(state->getSinglePiece(originalPos->getX(), originalPos->getY())->getIsDoublePiece())) {
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

bool BoardHelper::checkForCorrectDoublePieceMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	if (checkIfPieceToMoveIsCorrectColor(originalPos, state) && checkIfDestinationIsEmpty(movePosition, state))
	{
		if (checkIfLegalDoublePieceMove(originalPos, movePosition, state))
		{
			return true;
		}
	}
	return false;
}

bool BoardHelper::checkIfLegalDoublePieceMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	//check if every pos the piece moves over is not occupied

	int deltaXpos = movePosition->getX() - originalPos->getX();
	int deltaYpos = movePosition->getY() - originalPos->getY();

	if (deltaXpos == 0 || deltaYpos == 0)
	{
		return false;
	}

	int x = originalPos->getX();
	int y = originalPos->getY();

	//left up
	if (deltaXpos < 0 && deltaYpos < 0)
	{
		for (int i = 0; i < abs(deltaXpos) - 1; i++)
		{
			x -= 1;
			y -= 1;

			if (state->getSingleBoardPos(x, y)->checkOccupied() && i != abs(deltaXpos) - 2) {
				return false;
			}
			else if (state->getSingleBoardPos(x, y)->checkOccupied() && i == abs(deltaXpos) - 2) {
				if (state->getSinglePiece(x, y)->color != state->getSinglePiece(originalPos->getX(), originalPos->getY())->color)
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

			if (state->getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state->getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
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

			if (state->getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state->getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
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

			if (state->getSingleBoardPos(x, y)->checkOccupied() && i != (abs(deltaXpos) - 2)) {
				return false;
			}
			else if (state->getSingleBoardPos(x, y)->checkOccupied() && i == (abs(deltaXpos) - 2)) {
				return true;
			}
		}
		return true;
	}

	return false;
}

bool BoardHelper::checkForCorrectNormalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	if (!(state->getSinglePiece(originalPos->getX(), originalPos->getY())->getIsDoublePiece()));
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



bool BoardHelper::checkIfPieceToMoveIsCorrectColor(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardState> state) {
	Piece::PieceColor colorToMove = Piece::Black;
	if (state->whiteToMove)
	{
		colorToMove = Piece::White;
	}

	if (state->getSingleBoardPos(originalPos->getX(), originalPos->getY())->checkOccupied()) {
		if (state->getSinglePiece(originalPos->getX(), originalPos->getY())->color == colorToMove) {
			return true;
		}
	}
	return false;
}

bool BoardHelper::checkIfDestinationIsEmpty(std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	return !(state->getSingleBoardPos(movePosition->getX(), movePosition->getY())->checkOccupied());
}

bool BoardHelper::checkIfLegalNormalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state) {
	if (state->whiteToMove)
	{
		// left move
		if ((originalPos->getX() - 1) == movePosition->getX() && (originalPos->getY() + 1) == movePosition->getY())
		{
			return true;
		}

		// right move
		if ((originalPos->getX() + 1) == movePosition->getX() && (originalPos->getY() + 1) == movePosition->getY())
		{
			return true;
		}
	}
	else {
		// left move
		if ((originalPos->getX() - 1) == movePosition->getX() && (originalPos->getY() - 1) == movePosition->getY())
		{
			return true;
		}

		// right move
		if ((originalPos->getX() + 1) == movePosition->getX() && (originalPos->getY() - 1) == movePosition->getY())
		{
			return true;
		}
	}
	return false;
}

bool BoardHelper::obligatedToTake(std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake) {
	std::shared_ptr<std::vector<std::shared_ptr<Piece>>> currentPieces = getCurrentlyUsedPieces(state);

	for (std::shared_ptr<Piece> piece : *currentPieces) {
		if (checkIfPieceCanTake(piece, state, positionToTake)) {
			if (piece->color == 0) {
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



std::shared_ptr<std::vector<std::shared_ptr<Piece>>> BoardHelper::getCurrentlyUsedPieces(std::shared_ptr<BoardState> state) {
	bool whiteToMove = state->whiteToMove;
	std::shared_ptr<std::vector<std::shared_ptr<Piece>>> currentPieces = std::make_shared<std::vector<std::shared_ptr<Piece>>>();
	for (std::shared_ptr<Piece> piece : *state->getPieces()) {
		if (piece->color == piece->White && whiteToMove) {
			currentPieces->push_back(piece);
		}
		else if (piece->color == piece->Black && !whiteToMove) {
			currentPieces->push_back(piece);
		}
	}
	return currentPieces;
}

bool BoardHelper::checkIfPieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake) {
	if (!(piece->getIsDoublePiece())) { // single piece
		if (checkDirectionSinglePieceCanTake(piece, state, LEFTUP, positionToTake) || checkDirectionSinglePieceCanTake(piece, state, RIGHTUP, positionToTake) || checkDirectionSinglePieceCanTake(piece, state, LEFTDOWN, positionToTake) || checkDirectionSinglePieceCanTake(piece, state, RIGHTDOWN, positionToTake)) {
			return true;
		}
		else {
			return false;
		}
	}
	else { // double piece
		if (checkDircectionDoublePieceCanTake(piece, state, LEFTUP, positionToTake) || checkDircectionDoublePieceCanTake(piece, state, RIGHTUP, positionToTake) || checkDircectionDoublePieceCanTake(piece, state, LEFTDOWN, positionToTake) || checkDircectionDoublePieceCanTake(piece, state, RIGHTDOWN, positionToTake))
		{
			return true;
		}
		else {
			return false;
		}

	}


}

bool BoardHelper::checkDircectionDoublePieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, BoardHelper::directions direction, std::shared_ptr<BoardPos> positionToTake) {
	int x = piece->position->getX();
	int y = piece->position->getY();
	int xToCheck = x;
	int yToCheck = y;
	bool foundOpposingPiece = false;
	
	try {
		std::shared_ptr<BoardPos> potentialTakePos;
		for (int i = 0; i < state->getBoardSize(); i++) {
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


			std::shared_ptr<BoardPos> pos = state->getSingleBoardPos(xToCheck, yToCheck);

			if (pos->checkOccupied())
			{
				if (state->getSinglePiece(pos->getX(), pos->getY())->color == piece->color) {
					return false;
				}
				else {
					if (foundOpposingPiece)
					{
						return false;
					}
					foundOpposingPiece = true;
					

					potentialTakePos->setOccupied(pos->checkOccupied());
					potentialTakePos->setX(pos->getX());
					potentialTakePos->setY(pos->getY());
				}
			}
			else {
				if (foundOpposingPiece)
				{
					positionToTake->setOccupied(potentialTakePos->checkOccupied());
					positionToTake->setX(potentialTakePos->getX());
					positionToTake->setY(potentialTakePos->getY());
					return true;
				}
			}
		}

	}
	catch (const std::out_of_range& e) {
		return false;
	}
}

bool BoardHelper::checkDirectionSinglePieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, BoardHelper::directions direction, std::shared_ptr<BoardPos> positionToTake) {
	int x = piece->position->getX();
	int y = piece->position->getY();
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
		std::shared_ptr<BoardPos> currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (std::shared_ptr<Piece> currentPiece : *state->getPieces()) {
				if (currentPiece->position->getX() == currentPos->getX() && currentPiece->position->getY() == currentPos->getY() && currentPiece->color != piece->color) {

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
\
					positionToTake->setX(currentPos->getX());
					positionToTake->setY(currentPos->getY());
					positionToTake->setOccupied(currentPos->checkOccupied());

					currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
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

bool BoardHelper::checkLeftUp(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state) {
	//left up
	int x = piece->position->getX();
	int y = piece->position->getY();
	int xToCheck = x - 1;
	int yToCheck = y - 1;
	try {
		std::shared_ptr<BoardPos> currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (std::shared_ptr<Piece> currentPiece : *state->getPieces()) {
				if (currentPiece->position->getX() == currentPos->getX() && currentPiece->position->getY() == currentPos->getY() && currentPiece->color != piece->color) {
					xToCheck -= 1;
					yToCheck -= 1;
					currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
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

bool BoardHelper::checkRightUp(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state) {

	//right up
	int x = piece->position->getX();
	int y = piece->position->getY();
	int xToCheck = x + 1;
	int yToCheck = y - 1;

	try {
		std::shared_ptr<BoardPos> currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (std::shared_ptr<Piece> currentPiece : *state->getPieces()) {
				if (currentPiece->position->getX() == currentPos->getX() && currentPiece->position->getY() == currentPos->getY() && currentPiece->color != piece->color) {
					xToCheck += 1;
					yToCheck -= 1;
					currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
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

bool BoardHelper::checkLeftDown(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state) {
	//left down
	int x = piece->position->getX();
	int y = piece->position->getY();
	int xToCheck = x - 1;
	int yToCheck = y + 1;
	try {
		std::shared_ptr<BoardPos> currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (std::shared_ptr<Piece> currentPiece : *state->getPieces()) {
				if (currentPiece->position->getX() == currentPos->getX() && currentPiece->position->getY() == currentPos->getY() && currentPiece->color != piece->color) {
					xToCheck -= 1;
					yToCheck += 1;
					currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
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

bool BoardHelper::checkRightDown(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state) {

	//right down
	int x = piece->position->getX();
	int y = piece->position->getY();
	int xToCheck = x + 1;
	int yToCheck = y + 1;
	try {
		std::shared_ptr<BoardPos> currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
		if (currentPos->checkOccupied()) {
			for (std::shared_ptr<Piece> currentPiece : *state->getPieces()) {
				if (currentPiece->position->getX() == currentPos->getX() && currentPiece->position->getY() == currentPos->getY() && currentPiece->color != piece->color) {
					xToCheck += 1;
					yToCheck += 1;
					currentPos = state->getSingleBoardPos(xToCheck, yToCheck);
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

bool BoardHelper::checkIfPieceCanPromote(std::shared_ptr<Piece> piece) {
	if (piece->color == Piece::White && piece->position->getY() == 7) {
		return true;
	}
	else if (piece->color == Piece::Black && piece->position->getY() == 0) {
		return true;
	}

	return false;
}