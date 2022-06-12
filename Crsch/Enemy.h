#pragma once
#include "Map.h"
#include "Player.h"
#include "Person.h"
class Enemy:public Person
{
private:
	Player* player;
public:
	Enemy(Map*, Player*,int,int);
	void goToPlayer(double);
};

