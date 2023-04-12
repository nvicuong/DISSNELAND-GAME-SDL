#pragma once
#include <string>
#include <sstream>
#include "AssetManager.h"

class Map
{
public:

	int sizeWidthMap;
	int sizeHeightMap;
	int scaledSize;
	Map(std::string tID, int ms, int ts);
	~Map();
	void AddTile(int srcX, int srcY, int xpos, int ypos, int index);
	void LoadMap(std::string path, int sizeX, int sizeY);

private:
	std::string texID;
	int mapScale;
	int tileSize;
	
	
};