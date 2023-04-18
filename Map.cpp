#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"




extern Manager manager;
int Map::map1[20][50];

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
	
}

Map::~Map()
{
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{

	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			//std::cout << "c : " << c << "       ";
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			//std::cout << "c: " << c << std::endl;
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize, 0);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			//std::cout << "c : " << c << "       ";
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			//std::cout << "c: " << c << std::endl;
			srcX = atoi(&c) * tileSize;
			if (srcX != 9*tileSize && srcY != 9*tileSize)
			{
			AddTileBuilding(srcX, srcY, x * scaledSize, y * scaledSize, 0);
			}
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				map1[y][x] = 1;
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			else
			{
				map1[y][x] = 0;
			}
			mapFile.ignore();
		}
		// std::cout << std::endl;
	}

	mapFile.close();
	
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, int index)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID, index);
	tile.addGroup(Game::groupMap);
}

void Map::AddTileBuilding(int srcX, int srcY, int xpos, int ypos, int index)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID, index);
	tile.addGroup(Game::groupMapBuilding);
}

