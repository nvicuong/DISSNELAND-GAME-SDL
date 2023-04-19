#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component
{
public:
	bool followPlayer;
	ProjectileComponent(int rng, int sp, Vector2D vel, bool f) : range(rng), speed(sp), velocity(vel), followPlayer(f)
	{}
	~ProjectileComponent() {};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		//std::cout << transform->position << std::endl;
	}

	void update() override
	{
		distance += speed;

		if (distance > 1000)
		{
			entity->destroy();
		}
	}

	void follow(const SDL_Rect& recP)
	{
		if (followPlayer)
		{
			float newXposProj = recP.x + (recP.w / 2);
			float newYposProj = recP.y + (recP.h / 2);

			std::cout << newXposProj - transform->position.x << " " << newXposProj - transform->position.y << std::endl;
			transform->position.x = transform->position.x + (newXposProj - transform->position.x) * FOLLOW_PLAYER;
			transform->position.y = transform->position.y + (newXposProj - transform->position.y) * FOLLOW_PLAYER;

		}
	}


private:

	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

};
