#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;


	ColliderComponent(int xpos, int ypos, int size)
	{
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	void init() override
	{
		
		tex = TextureManager::LoadTexture("assets/coltex.png");
		srcR = { 0, 0, 32, 32 };
		destR = { collider.x, collider.y, collider.w, collider.h };
	
	}

	void update() override
	{
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;

	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}

};

