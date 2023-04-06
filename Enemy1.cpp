#include "Enemy1.h"

std::vector<float> desX = { -1, -0.95, -0.9, -0.85, -0.8, -0.75, -0.7, -0.65, -0.6, -0.55, -0.5, -0.45, -0.4, -0.35, -0.3, -0.25, -0.2, -0.15, -0.1, -0.05, 0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1 };
std::vector<float> desY = { -1, -0.95, -0.9, -0.85, -0.8, -0.75, -0.7, -0.65, -0.6, -0.55, -0.5, -0.45, -0.4, -0.35, -0.3, -0.25, -0.2, -0.15, -0.1, -0.05, 0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1 };

float getPosDesY(float posX, float radios)
{
	float posY = sqrt((radios * radios) - (posX * posX));
	return posY;
}
Animation aniProject[] = {
	Animation(4, 100, 10, 15),
	Animation(4, 100, 10, 15)
};
int sizeaniProject = 2;

bool flip = 0;
void Enemy1::walkAround()
{
	distance += speed;

	if (distance > 500)
	{
		if (flip)
		{
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			flip = 0;
		}
		else
		{
			sprite->spriteFlip = SDL_FLIP_NONE;
			flip = 1;
		}
		transform->velocity.x = -transform->velocity.x;
		distance = 0;
	}
}


Vector2D Enemy1::getVel(const SDL_Rect& eneRect, const SDL_Rect& recP)
{
	float posX = transform->position.x;
	float posY = transform->position.y;

	float radios = 1;
	float gDesX = posX + (-1) * 200;
	float gDesY = posY + (-1) * 200;

	float idX = 0;
	float idY = 0;

	//viet phuong trinh duong thang
	float a = std::pow(recP.x + recP.w/2 - gDesX, 2) + std::pow(recP.y + recP.h/2 - gDesY, 2);
	for (auto i : desX)
	{
		for (auto j : desY)
		{
			gDesX = posX + i * 200;
			gDesY = posY + j * 200;
			float b = std::pow(recP.x + recP.w/2 - gDesX, 2) + std::pow(recP.y + recP.h/2 - gDesY, 2);
			if (a > (std::min(a, b)))
			{
				a = b;
				idX = i;
				idY = j;

			}
		}
	}
	
	while (idX * idX + idY * idY < 1 && !(idX == 0 && idY == 0) && (idX != 0 || idY != 0))
	{
		idX *= 2;
		idY *= 2;
	}
	//std::cout << "idX: " << idX << " idY: " << idY << std::endl;
	return Vector2D(idX, idY);
}

void Enemy1::fireGun(const SDL_Rect& eneRect, const SDL_Rect& recP, AssetManager* assets)
{
	if (Collision::findAABB(eneRect, recP))
	{
		float posX = transform->position.x;
		float posY = transform->position.y;
		Vector2D getV = Enemy1::getVel(eneRect, recP);
		assets->CreateProJectile(Vector2D(posX, posY), getV, 10, 10, 200, 2, "projectile", 0, aniProject, sizeaniProject);
		
	}
}

void Enemy1::huntPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP)
{
	if (Collision::findAABB(eneRect, recP))
	{
		Vector2D getV = Enemy1::getVel(eneRect, recP);
		transform->velocity = getV;
	}
	else
	{
		Vector2D getV(0, 0);
		transform->velocity = getV;
	}
}

void Enemy1::attackPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP, bool attacked)
{	
	if (!attacked)
	{
	Enemy1::huntPlayer(eneRect, recP);
	if (transform->velocity.x > 0)
	{
		sprite->spriteFlip = SDL_FLIP_NONE;
	}
	else
	{
		sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	if (Collision::findAABB(eneRect, recP))
	{
		if (Collision::AABB(eneRect, recP))
		{
			if (unAttack == 1)
			{
				sprite->currentFrame = 0;
				unAttack = 0;
				sprite->timer = 0;
			}
			sprite->index = 3;
			sprite->hit = 1;
			sprite->Play(tag);
			if (sprite->hit == 1 && sprite->currentFrame == 7 && sprite->unHitCheck == 0)
			{
				hit = 1;
				sprite->unHit = 0;
				sprite->unHitCheck = 1;
			}
			else
			{
				hit = 0;
				sprite->unHit = 1;
			}
			if (sprite->currentFrame != 7)
			{
				sprite->unHitCheck = 0;
			}
			/*transform->velocity.x = 0;
			transform->velocity.y = 0;*/
		}
		else
		{
			unAttack = 1;
			//std::cout << "walk";
			sprite->index = 1;
			sprite->hit = 0;
			//sprite->timer = 0;
			//sprite->currentFrame = 0;
			sprite->Play(tag);
		}
	}
	else
	{
		unAttack = 1;
		sprite->index = 0;
		sprite->Play(tag);
	}
	}
	else
	{
		transform->velocity = Vector2D(0, 0);
		unAttack = 1;
		sprite->index = 0;
		sprite->Play(tag);
	}
}