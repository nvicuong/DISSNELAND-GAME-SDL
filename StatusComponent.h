#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "ColliderComponent.h"

class StatusBar : public Component
{
public:
	int health = 100;
	int mana = 100;
	int width = 32;
	StatusBar(int h, int m, int w) : health(h), mana(m), width(w)
	{}
	StatusBar() = default;
	~StatusBar() {};


	void init() override
	{
		transform = entity->getComponent<TransformComponent>();
		texture = TextureManager::LoadTexture("assets/health.png");
		//transform.position.y -= 30;
		transform.width = 10;
		transform.height = 5;
		srcRect.x = srcRect.y = 0;
		srcRect.w = 50;
		srcRect.h = 4;

	}

	void update() override
	{
		transform.position.x = entity->getComponent<TransformComponent>().position.x;
		transform.position.y = entity->getComponent<TransformComponent>().position.y - 10;
		//transform.width = 30;
		//transform->height = height;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = health/2;
		//srcRect.h = height;
		//std::cout << animIndex << std::endl;

		destRect.x = static_cast<int>(transform.position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform.position.y) - Game::camera.y;
		/*destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;*/

		destRect.w = (static_cast<double>(width)/50 * srcRect.w) * transform.scale;
		destRect.h = transform.height * transform.scale;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

	void getDamage(const SDL_Rect& rec, const SDL_Rect& recP);
private:
	TransformComponent transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};