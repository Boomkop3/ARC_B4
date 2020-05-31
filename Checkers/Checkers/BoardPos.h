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
	void setX(int x);
	int getY();
	void setY(int y);
	bool checkOccupied();
	void setOccupied(bool isOccupied);
	
};

