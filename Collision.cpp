#include "Collision.h"
#include "ColliderComponent.h"
#include <algorithm>
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::findAABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	int disX = std::max(recB.x - recA.x, recB.x - recA.x - recA.w);
	int disY = std::max(recB.y - recA.y, recB.y - recA.y - recA.h);
	if (disX <= 600 && disY <= 600)
	{
		return true;
	}
	return false;
}
