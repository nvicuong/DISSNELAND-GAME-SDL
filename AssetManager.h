#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include <vector>
#include <SDL2/SDL_ttf.h>


class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//gameObjects

	void CreateProJectile(Vector2D pos, Vector2D vel, int width, int height, int range, int speed, std::string id, int index, Animation idArray[], int sizeidArray);
	void CreateEnemy1(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray);
	void CreateEnemy2(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray);
	void CreateBoss(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray);
	void CreateThuoc(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray, int f);

	//texture management
	void AddVector(std::string id);
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id, int index);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, std::vector<SDL_Texture*>> textures;
	std::map<std::string, TTF_Font*> fonts;
};
