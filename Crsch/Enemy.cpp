#include "Enemy.h"

Enemy::Enemy(Map*mp, Player*pl,int x,int y):Person(mp,x*100+50,y*100+50)
{
	player = pl;
}

void Enemy::goToPlayer(double step)
{
	double nwx;
	double nwy;
	if (player->getX() > x)
		nwx=x+ step;
	else if (player->getX() < x)
		nwx = x - step;
	if (player->getY() > y)
		nwy=y + step;
	else if (player->getY() < y)
		nwy=y - step;
	if (map->at(static_cast<int>(nwx / 100), static_cast<int>(nwy / 100)) != 1) {
		x = nwx;
		y = nwy;
	}
}
