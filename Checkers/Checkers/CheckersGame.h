#pragma once
#include "BoardState.h"
class CheckersGame
{
public:
	//attributes
	BoardState boardState;
	enum CheckerState {ValidMove, InvalidMove, GameCompleted};

private:
	//functions
	CheckerState updateMove(BoardPos originalPos, std::vector<BoardPos> movePositions);
	BoardState getBoardState();
};

