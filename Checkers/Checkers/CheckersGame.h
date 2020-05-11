#pragma once
#include "BoardInfo.h"
class CheckersGame
{
public:
	//attributes
	BoardInfo boardInfo;
	enum CheckerState {ValidMove, InvalidMove, GameCompleted};

private:
	//functions
	CheckerState updateMove(BoardPos originalPos, std::vector<BoardPos> movePositions);
	BoardInfo getBoardInfo();
};

