#pragma once
#include "BoardState.h"
class CheckersGame
{
public:
	//attributes
	//BoardState boardState;
	std::shared_ptr<BoardState> boardState;
	typedef enum CheckerState {ValidMove, InvalidMove, GameCompleted} CheckerState;

private:
	std::shared_ptr<CheckersGame::CheckerState> updateMove(std::shared_ptr<BoardPos> originalPos, std::vector<std::shared_ptr<BoardPos>> movePositions);
	//functions
	/*std::shared_ptr<CheckerState> updateMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition);*/
	std::shared_ptr<BoardState> getBoardState();
};

