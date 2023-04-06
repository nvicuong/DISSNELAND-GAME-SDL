#pragma once
#include <SDL2/SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB1(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB1(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB2(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB2(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool findAABB(const SDL_Rect& recA, const SDL_Rect& recB);
};