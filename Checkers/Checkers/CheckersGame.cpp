#include "CheckersGame.h"


//CheckersGame::CheckerState CheckersGame::updateMove(BoardPos originalPos, BoardPos movePosition)
//{
//	//move logics
//	return CheckerState();
//}

//std::shared_ptr<CheckerState> updateMove(std::shared_ptr<BoardPos> originalPos, std::vector<std::shared_ptr<BoardPos>> movePositions)
//{
//	return std::shared_ptr<CheckerState>();
//}

std::shared_ptr<CheckersGame::CheckerState> CheckersGame::updateMove(std::shared_ptr<BoardPos> originalPos, std::vector<std::shared_ptr<BoardPos>> movePositions)
{
	//Move logics
	//return CheckerState;
	return NULL;
}

std::shared_ptr<BoardState> CheckersGame::getBoardState()
{
	return this->boardState;
}
