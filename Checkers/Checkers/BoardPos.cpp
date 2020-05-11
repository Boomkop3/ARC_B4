#include "BoardPos.h"

BoardPos::BoardPos() {
	//code werkt niet zonder deze default constructor, laat deze dus staan!!!
	x = 999;
	y = 999;
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


