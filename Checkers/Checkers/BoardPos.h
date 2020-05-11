#pragma once
class BoardPos
{
private:
	//attribute
	int x, y;
	bool isOccupied;

public:
	BoardPos();
	//function
	BoardPos(int xPos, int yPos);
	int getX();
	int getY();
	bool checkOccupied();
	void setOccupied(bool isOccupied);
	
};

