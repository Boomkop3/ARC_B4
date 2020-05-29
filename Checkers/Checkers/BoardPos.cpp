#include "BoardPos.h"

BoardPos::BoardPos() {
	//wanneer opgehaalde values de onderstaande zijn betekend dit dat er een valse positie is. (deze moet dus nog worden veranderd)
	x = -1;
	y = -1;
	isOccupied = false;
}

BoardPos::BoardPos(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	isOccupied = false;
}

int BoardPos::getX()
{
	return x;
}

int BoardPos::getY()
{
	return y;
}

bool BoardPos::checkOccupied()
{
	return isOccupied;
}

void BoardPos::setOccupied(bool _isOccupied)
{
	isOccupied = _isOccupied;
}


