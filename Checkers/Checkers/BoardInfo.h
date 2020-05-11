#pragma once
#include "BoardState.h"
class BoardInfo
{
public:
	BoardState boardState;
	bool whiteToMove;
	bool gameFinished;

private:
	bool checkGameFinished();
};

