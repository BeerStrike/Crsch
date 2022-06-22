#pragma once
#include "Map.h"
#include "person.h"
#include "Player.h"
class Player;
class Enemy:public Person
{
private:
	Player* player;
public:
	Enemy(Map*, Player*,int,int);
	void goToPlayer(double);
};

