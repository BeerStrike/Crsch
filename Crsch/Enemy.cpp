#include "Enemy.h"

Enemy::Enemy(Map*mp, Player*pl,int x,int y):Person(mp,x*100+50,y*100+50,100)
{
	player = pl;
}

bool Enemy::goToPlayer(double step)
{
	double nwx;
	double nwy;
	if (player->getX()-x >5)
		nwx = x + step;
	else if (player->getX() -x< -5)
		nwx = x - step;
	else nwx = x;
	if (player->getY()-y > 5)
		nwy = y + step;
	else if (player->getY()-y < -5)
		nwy = y - step;
	else
		nwy = y;
	if (map->at(static_cast<int>(nwx / 100), static_cast<int>(nwy / 100)) ==0 ) {
		x = nwx;
		y = nwy;
	}
		if (sqrt(pow(player->getX() - x, 2) + pow(player->getY()-y, 2)) < 30)
			return player->getDamage(3);
		return false;
}
