#pragma once
#include "Map.h"
class Person
{
protected:
	double x;
	double y;
	Map* map;
public:
	Person(Map*,int,int);
	int getX();
	int getY();
};

