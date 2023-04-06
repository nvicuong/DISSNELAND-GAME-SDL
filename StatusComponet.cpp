#include "StatusComponent.h"

void StatusBar::getDamage(const SDL_Rect& rec, const SDL_Rect& recP)
{
	if (Collision::AABB(rec, recP))
	{
		//health -= 10;
	}
}