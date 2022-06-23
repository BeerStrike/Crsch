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
	void raycast(double*,int, std::vector<Enemy*>&);
	void enemycast(std::vector<double>&, std::vector<Enemy*>&);
	double getAngle();
};

