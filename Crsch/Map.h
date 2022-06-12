#pragma once
#include <fstream>
#include <string>
#include <vector>
class Map
{
private:
	Map(std::ifstream& fin);
	int size;
	int** map;
	int startx;
	int starty;
	std::vector<int> enemiesX;
	std::vector<int> enemiesY;
public:
	static Map* make(std::string);
	int at(int, int);
	int getSize();
	int getPlayerX();
	int getPlayerY();
	int getEnemiesNum();
	int getEnemiesX(int);
	int getEnemiesY(int);
	~Map();
};

