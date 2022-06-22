#pragma once
#include "Map.h"
#include "person.h"
#include <vector>
#include "Enemy.h"
class Enemy;
class Player:public Person
{
private:
	double angle;
public:
	Player(Map*);
	bool movefrw(double);
	bool moveBack(double);
	void rotateLeft(double);
	void rotateRight(double);
	void shot(std::vector<Enemy*>&);
	double* raycast(int, std::vector<Enemy*>&);
	double* enemycast(int, std::vector<Enemy*>&);
	double getAngle();
};

