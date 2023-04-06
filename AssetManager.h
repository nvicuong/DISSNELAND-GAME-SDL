#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include <vector>


class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//gameObjects

	void CreateProJectile(Vector2D pos, Vector2D vel, int width, int height, int range, int speed, std::string id, int index, Animation idArray[], int sizeidArray);
	void CreateEnemy1(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray);
	void CreateEnemy2(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray);

	//texture management
	void AddVector(std::string id);
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id, int index);

private:
	Manager* manager;
	std::map<std::string, std::vector<SDL_Texture*>> textures;
};
