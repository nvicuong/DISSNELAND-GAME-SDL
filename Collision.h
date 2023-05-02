#pragma once
#include <SDL2/SDL.h>


class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool findAABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool colRight(int Px, int Py, int Cx, int Cy);
	static bool colLeft(int Px, int Py, int Cx, int Cy);
	static bool colUp(int Px, int Py, int Cx, int Cy);
	static bool colDown(int Px, int Py, int Cx, int Cy);
};