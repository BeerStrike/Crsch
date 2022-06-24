#pragma once
#include "Map.h"
class Person
{
protected:
	double x;
	double y;
	Map* map;
	int hp;
public:
	Person(Map*,int,int,int);
	int getX();
	int getY();
	bool getDamage(int);
	int getHP();
};

