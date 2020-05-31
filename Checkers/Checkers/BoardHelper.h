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
	void RemovePiece(std::shared_ptr<BoardPos> position, std::shared_ptr<BoardState> state);
	void MakeDoublePiece(std::shared_ptr<BoardPos> position, std::shared_ptr<BoardState> state);
	BoardHelper::checkerstate makeMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool checkIfLegalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake);
	bool checkForCorrectDoublePieceMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool checkForCorrectNormalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool checkIfLegalDoublePieceMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool checkIfPieceToMoveIsCorrectColor(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardState> state);
	bool checkIfDestinationIsEmpty(std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool checkIfLegalNormalMove(std::shared_ptr<BoardPos> originalPos, std::shared_ptr<BoardPos> movePosition, std::shared_ptr<BoardState> state);
	bool obligatedToTake(std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake);
	
private:
	std::shared_ptr<std::vector<std::shared_ptr<Piece>>> getCurrentlyUsedPieces(std::shared_ptr<BoardState> state);
	bool checkIfPieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, std::shared_ptr<BoardPos> positionToTake);
	bool checkDircectionDoublePieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, BoardHelper::directions direction, std::shared_ptr<BoardPos> positionToTake);
	bool checkDirectionSinglePieceCanTake(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state, BoardHelper::directions direction, std::shared_ptr<BoardPos> positionToTake);
	bool checkLeftUp(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state);
	bool checkRightUp(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state);
	bool checkLeftDown(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state);
	bool checkRightDown(std::shared_ptr<Piece> piece, std::shared_ptr<BoardState> state);
	bool checkIfPieceCanPromote(std::shared_ptr<Piece> piece);
};


