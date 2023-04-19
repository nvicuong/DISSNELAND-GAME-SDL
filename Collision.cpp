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
		/*std::cout << "recA.x = " << recA.x << "......" << "recA.w = " << recA.w << std::endl
			<< "recA.y = " << recA.y << "......" << "recA.h = " << recA.h << std::endl
			<< "recB.x = " << recB.x << "......" << "recB.w = " << recB.w << std::endl
			<< "recB.y = " << recB.y << "......" << "recB.h = " << recB.h << std::endl;*/
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Collision::AABB1(const SDL_Rect& recA, const SDL_Rect& recB)
{
		/*std::cout << "recA.x = " << recA.x << "......" << "recA.w = " << recA.w << std::endl
			<< "recA.y = " << recA.y << "......" << "recA.h = " << recA.h << std::endl
			 << "recB.x = " << recB.x << "......" << "recB.w = " << recB.w << std::endl
			<< "recB.y = " << recB.y << "......" << "recB.h = " << recB.h << std::endl;*/
	if (recA.x + recA.w - recB.x >= 0)
	{
		return true;
	}
	return false;
}

bool Collision::AABB1(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB1(colA.collider, colB.collider))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Collision::AABB2(const SDL_Rect& recA, const SDL_Rect& recB)
{
	/*std::cout << "recA.x = " << recA.x << "......" << "recA.w = " << recA.w << std::endl
		<< "recA.y = " << recA.y << "......" << "recA.h = " << recA.h << std::endl
		<< "recB.x = " << recB.x << "......" << "recB.w = " << recB.w << std::endl
		<< "recB.y = " << recB.y << "......" << "recB.h = " << recB.h << std::endl;*/
	if (

		//((recA.x + recA.w >= recB.x && recA.x + recA.w <= recB.x + recB.w) || (recA.x <= recB.x + recB.w && recA.x >= recB.x) || (recA.x + recA.w >= recB.x + recB.w && recB.x >= recA.x))
		//(recA.y + recA.h - recB.y > -3 && recA.y + recA.h - recB.y <= 3)
		//recB.x - recA.x - recA.w <= 0 || recA.x - recB.x - recB.w <= 0
		recA.y + recA.h - recB.y >= 0 && recA.y + recA.h - recB.y <= 6
		)
		//std::cout << recA.x + recA.w - recB.x - recB.w << " " << recA.y + recA.h - recB.y << std::endl;
	{
		return true;
	}
	return false;
}


bool Collision::AABB2(const ColliderComponent& colA, const ColliderComponent& colB)
{

	if (AABB2(colA.collider, colB.collider))
	{
		return true;
	}
	else
	{
		return false;
	}
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
