#include "BoardPos.h"
#include "BoardState.h"
#include <vector>

class BoardHelper
{


public:
	//enums
	enum checkerstate { VALIDMOVE, INVALIDMOVE, GAMECOMPLETED };
	enum directions { LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN };
	//functies
	void RemovePiece(BoardPos& position, BoardState& state);
	void MakeDoublePiece(BoardPos& position, BoardState& state);
	BoardHelper::checkerstate makeMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool checkIfLegalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool checkForCorrectDoublePieceMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool checkForCorrectNormalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool checkIfLegalDoublePieceMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool checkIfPieceToMoveIsCorrectColor(BoardPos& originalPos, BoardState& state);
	bool checkIfDestinationIsEmpty(BoardPos& movePosition, BoardState& state);
	bool checkIfLegalNormalMove(BoardPos& originalPos, BoardPos& movePosition, BoardState& state);
	bool obligatedToTake(BoardState& state);
	
private:
	std::vector<Piece> getCurrentlyUsedPieces(BoardState& state);
	bool checkIfPieceCanTake(Piece piece, BoardState& state);
	bool checkDircectionDoublePieceCanTake(Piece piece, BoardState& state, BoardHelper::directions direction);
	bool checkDirectionSinglePieceCanTake(Piece piece, BoardState& state, BoardHelper::directions direction);
	bool checkLeftUp(Piece piece, BoardState& state);
	bool checkRightUp(Piece piece, BoardState& state);
	bool checkLeftDown(Piece piece, BoardState& state);
	bool checkRightDown(Piece piece, BoardState& state);

	bool checkIfPieceCanPromote(Piece piece);
	
	
};


