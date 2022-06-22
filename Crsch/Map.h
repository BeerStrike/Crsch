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
public:
	static Map* load(std::string);
	int at(int, int);
	int getSize();
	int getPlayerX();
	int getPlayerY();
	void setCell(int, int, int);
	~Map();
};

