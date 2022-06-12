#pragma once
#include "Map.h"
#include "person.h"
class Player:public Person
{
private:
	double angle;
public:
	Player(Map*);
	void movefrw(double);
	void moveBack(double);
	void rotateLeft(double);
	void rotateRight(double);
	double* raycast(int);
	double getAngle();
};

