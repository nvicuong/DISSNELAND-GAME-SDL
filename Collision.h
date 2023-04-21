#pragma once
#include <SDL2/SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool findAABB(const SDL_Rect& recA, const SDL_Rect& recB);
};