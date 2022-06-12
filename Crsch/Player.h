#pragma once
#include "Map.h"
class Player
{
private:
	double x;
	double y;
	double angle;
	Map *map;
public:
	Player(Map*);
	void movefrw(double);
	void moveBack(double);
	void rotateLeft(double);
	void rotateRight(double);
	double* raycast(int);
	int getX();
	int getY();
	double getAngle();
};

