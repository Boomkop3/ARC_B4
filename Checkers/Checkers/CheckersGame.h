#pragma once
#include "BoardState.h"
class CheckersGame
{
public:
	//attributes
	BoardState boardState;
	enum CheckerState {ValidMove, InvalidMove, GameCompleted};

private:
	CheckersGame::CheckerState updateMove(BoardPos originalPos, std::vector<BoardPos> movePositions);
	//functions
	CheckerState updateMove(BoardPos originalPos, BoardPos movePosition);
	BoardState getBoardState();
};

