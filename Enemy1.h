#pragma once
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
	int hit;
	//bien kiem tra xem enemy co bi gay sat thuong khong
	double hurtedTimer = 0;
	bool checkHurted = 0;
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
		hurtedTimer = 2;
		hit = 0;
		checkHurted = 0;
		attacked = 0;
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
	bool completedAttack();
	void fireGun(const SDL_Rect &eneRect, const SDL_Rect& recP, AssetManager* assets);
	bool huntPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP);
	void attackPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP);
	void getHurt();

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	std::string tag;
	int speed = 0;
	int distance = 0;
};