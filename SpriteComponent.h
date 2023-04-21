#pragma once

#include "Components.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;
	int width = 32;
	int height = 32;
	int speed = 100;

public:
	std::string tag;
	SDL_Rect posRect;
	int frames = 0;
	int timer = 0;
	Uint32 periodTime = 0;
	Uint32 latterTime = 0;
	int deltaTime = 0;
	int currentFrame = 0;
	bool dead = 0;
	bool stillDead = 0;
	int index = 0;


	std::map<std::string, std::map<int, Animation>> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;
	

	SpriteComponent(std::string id, Animation idArray[], int sizeidArray)
	{
		tag = id;
		

		for (int i = 0; i < sizeidArray; ++i)
		{
			animations[id].emplace(i, idArray[i]);
		}


		Play(id);
		//setTex(id, index);
	}

	~SpriteComponent()
	{

	}
	void setTex(std::string id, int index)
	{
		texture = Game::assets->GetTexture(id, index);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		currentFrame = 0;
		timer = 0;
		periodTime = 0;
		latterTime = SDL_GetTicks();
		deltaTime = latterTime - periodTime;
		transform->width = width;
		transform->height = height;
		srcRect.x = srcRect.y = 0;
		srcRect.w = width;
		srcRect.h = height;
		posRect = {static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), width, height};

	}

	void update() override
	{
		periodTime = latterTime;
		latterTime = SDL_GetTicks();
		deltaTime = latterTime - periodTime;
	
		timer += deltaTime;
		if (timer > speed )
		{
			currentFrame++;
			timer = 0;
		}

		
		if (currentFrame > frames - 1)
		{
			if (stillDead)
			{
				currentFrame = frames - 1;
			}
			else
			{
			currentFrame = 0;
			}
		}

		/*transform->width = width;
		transform->height = height;*/

		srcRect.x = width * currentFrame;

		srcRect.y = 0;
		srcRect.w = width;
		srcRect.h = height;
		

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;


		destRect.w = width * transform->scale;
		destRect.h = transform->height * transform->scale;
		

		posRect.x = static_cast<int>(transform->position.x);
		posRect.y = static_cast<int>(transform->position.y);
		posRect.w = width * transform->scale;
		posRect.h = transform->height * transform->scale;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(std::string animName)
	{
		
		frames = animations[animName][index].frames;
		speed = animations[animName][index].speed;
		width = animations[animName][index].width;
		height = animations[animName][index].height;
		
		setTex(animName, index);
		
		
		//std::cout << "width: " << width << "  height: " << height << std::endl;
	}


};