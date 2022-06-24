#pragma once
#include <fstream>
#include <string>
#include <vector>
class Map
{
private:
	Map(std::ifstream& fin, std::string);
	int size;
	int** map;
	int startx;
	int starty;
	std::string MapName;
public:
	static Map* load(std::string);
	int at(int, int);
	int getSize();
	int getPlayerX();
	int getPlayerY();
	std::string getMapName();
	void setCell(int, int, int);
	~Map();
};

