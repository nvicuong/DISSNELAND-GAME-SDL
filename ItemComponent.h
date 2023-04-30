#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class Item : public Component
{
public:
	Item(int f) : index(f)
	{}
	~Item() {};

	void init() override
	{
        x = 0;
		transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        sprite->index = index;
        sprite->Play("item");
        xpos = transform->position.x;
        ypos = transform->position.y;
	}

	void update() override
	{
        if (x <= 2)
        {
            double delta = (x-1)*(x-1);
            transform->position.y = ypos + 40*delta;
            x += 0.02;
        }
	}

    bool check()
    {
        if (x >= 2)
        {
            return true;
        }
        return false;
    }

    int getIndex()
    {
        return index;
    }

private:

	TransformComponent* transform;
    SpriteComponent* sprite;
    double xpos;
    double ypos;
	double x = 0;
	int index = 0;

};
