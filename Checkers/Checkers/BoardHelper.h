#include "BoardPos.h"
#include "BoardState.h"
#include <vector>

class BoardHelper
{
public:
	//functies
	void RemovePiece(BoardPos& position, BoardState& state);
	void MakeDoublePiece(BoardPos& position, BoardState& state);
	bool checkIfLegalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool obligatedToTake(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);

private:
	std::vector<Piece> getCurrentlyUsedPieces(BoardState& state);
	bool checkIfPieceCanTake(Piece piece, BoardState& state);
	bool checkLeftUp(Piece piece, BoardState& state);
	bool checkRightUp(Piece piece, BoardState& state);
	bool checkLeftDown(Piece piece, BoardState& state);
	bool checkRightDown(Piece piece, BoardState& state);
};

bool checkLeftUp(Piece piece, BoardState& state);
