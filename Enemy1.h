#pragma once
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Define.h"
#include "ColliderComponent.h"
#include <cmath>

class Enemy1 : public Component
{
public:
	double periodTime = 0;
	double timer = 0;
	bool attacked;
	bool check;
	int hit = 0;
	//SDL_Rect* eneRect;
	Enemy1(int sp, std::string t) : speed(sp), tag(t)
	{}
	~Enemy1() {};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		sprite->index = 0;
		periodTime = SDL_GetTicks()/1000;
		timer = 5;
		hit = 0;
		attacked = 0;
		check = 0;
		unAttack = 0;
		transform->velocity.x = -1;
		transform->velocity.y = 0;
		transform->speed = 1;
		sprite->Play(tag);
		//eneRect = &entity->getComponent<ColliderComponent>().collider;
	}

	void update() override
	{
		if (tag == "enemy1")
		{
			walkAround();
		}
		if (tag == "enemy2")
		{

		}
	}

	Vector2D getVel(const SDL_Rect& eneRect, const SDL_Rect& recP);
	void walkAround();
	void fireGun(const SDL_Rect &eneRect, const SDL_Rect& recP, AssetManager* assets);
	void huntPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP);
	void attackPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP, bool attacked);

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	std::string tag;
	bool unAttack = 0;
	int speed = 0;
	int distance = 0;
};