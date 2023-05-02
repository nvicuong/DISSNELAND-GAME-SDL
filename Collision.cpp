#include "Collision.h"
#include "ColliderComponent.h"
#include <algorithm>

int dXRL[] = {-1, 0, 0, 0};
int dYRL[] = {1, 1,-1, 0};



int dXUD[] = {-1, 0, 1};
int dYUD[] = {0, 0, 0};

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
	if (disX <= 400 && disY <= 400)
	{
		return true;
	}
	return false;
}

bool Collision::colRight(int Px, int Py, int Cx, int Cy)
{
	for (int i = 0; i < 2; i++)
	{
		if (Px+dXRL[i] == Cx && Py+dYRL[i] == Cy)
		{ return true; }
	}
	return false;
}

bool Collision::colLeft(int Px, int Py, int Cx, int Cy)
{
	for (int i = 2; i < 4; i++)
	{
		if (Px+dXRL[i] == Cx && Py+dYRL[i] == Cy)
		{ return true; }
	}
	return false;
}

bool Collision::colUp(int Px, int Py, int Cx, int Cy)
{
	for (int i = 0; i < 2; i++)
	{
	if (Px + dXUD[i] == Cx && Py+ dYUD[i] == Cy)
	{ return true; }
	}
	return false;
}

bool Collision::colDown(int Px, int Py, int Cx, int Cy)
{
	
	if (Px+dXUD[2] == Cx && Py+dYUD[2] == Cy)
	{ return true; }
	
	return false;
}
