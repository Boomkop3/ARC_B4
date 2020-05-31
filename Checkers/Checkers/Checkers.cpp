#include "BoardHelper.h"

int main()
{
    std::shared_ptr<BoardState> state = std::make_shared<BoardState>();
	state->whiteToMove = true;
    std::shared_ptr<BoardHelper> h = std::make_shared<BoardHelper>();

	state->addPieceToPosition(4, 4, Piece::White, false);
	state->addPieceToPosition(3, 3, Piece::Black, false);
	state->addPieceToPosition(5, 5, Piece::Black, false);

	// Met wit slaan lukt, maar met zwart klopt de positie niet meer? Misschien een kleine bug die er in is gekomen bij het omzetten naar pointers?
	
	state->printBoard();
	h->makeMove(std::make_shared<BoardPos>(4, 4), std::make_shared<BoardPos>(2, 2), state);
	state->printBoard();

}

