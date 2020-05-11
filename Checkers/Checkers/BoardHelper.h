#include "BoardPos.h"
#include "BoardState.h"
#include <vector>

class BoardHelper
{
public:
	//functies
	void RemovePiece(BoardPos& position, BoardState& state);
	void MakeDoublePiece(BoardPos& position, BoardState& state);
	bool checkIfLegalMove(BoardPos& originalPos, std::vector<BoardPos>& movePositions);
};

