#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class Enemy1;
class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
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


private:

	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

};
