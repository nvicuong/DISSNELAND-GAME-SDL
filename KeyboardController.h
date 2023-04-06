#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	bool hit = 0;
	bool unKey = 0;
	bool stopWalk = 0;
	TransformComponent* transform;
	SpriteComponent* sprite;
	char stateKeyUp = '\0';
	char stateKeyDown = '\0';

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		//std::cout << "timer: " << sprite->timer << std::endl;
		//std::cout << "currentFrames: " << sprite->currentFrame << std::endl;
		if (Game::event.type == SDL_KEYDOWN && sprite->dead == 0)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//std::cout << "W" << std::endl;
				stateKeyDown = 'w';
				transform->velocity.y = -1;
				sprite->index = 1;
				sprite->Play("player");
				break;
			case SDLK_a:
				//std::cout << "A" << std::endl;
				stateKeyDown = 'a';
				transform->velocity.x = -1;
				sprite->index = 1;
				sprite->Play("player");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				stopWalk = 1;
				break;
			case SDLK_d:
				//std::cout << "D" << std::endl;
				/*if (stateKeyDown == 'a' && stateKeyUp != 'a')
				{
				}*/
				stateKeyDown = 'd';
				transform->velocity.x = 1;
				sprite->index = 1;
				sprite->spriteFlip = SDL_FLIP_NONE;
				stopWalk = 0;
				sprite->Play("player");
				break;
			case SDLK_s:
				//std::cout << "S" << std::endl;
				stateKeyDown = 's';
				transform->velocity.y = 1;
				sprite->index = 1;
				sprite->Play("player");
				break;
			case SDLK_h:
				stateKeyDown = 'h';
				sprite->index = 2;
				sprite->Play("player");
				break;
			case SDLK_j:
				stateKeyDown = 'j';
				if (unKey == 1)
				{
					sprite->currentFrame = 0;
					unKey = 0;
					sprite->timer = 0;
				}
				//std::cout << "j" << std::endl;
				sprite->index = 3;
				sprite->hit = 1;
				sprite->Play("player");
				//std::cout << "curren: " << sprite->currentFrame << std::endl;
				if (sprite->hit == 1 && (sprite->currentFrame == 5 || sprite->currentFrame == 9) && sprite->unHitCheck == 0)
				{
					//std::cout << "...." << sprite->currentFrame << std::endl;
					hit = 1;
					sprite->unHit = 0;
					sprite->unHitCheck = 1;
				}
				else
				{
					hit = 0;
					sprite->unHit = 1;
				}
				if (sprite->currentFrame != 3)
				{
					sprite->unHitCheck = 0;
				}
				transform->velocity = Vector2D(0, 0);
				
				//stateKeyUp = 1;
				break;
			case SDLK_k:
				stateKeyDown = 'k';
				sprite->index = 4;
				sprite->Play("player");
				break;
			default:
				
				break;
			}

		}

		if (Game::event.type == SDL_KEYUP && sprite->dead == 0)
		{
			
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//std::cout << "w up" << std::endl;
				stateKeyUp = 'w';
				unKey = 1;
				transform->velocity.y = 0;
				sprite->index = 0;
				sprite->Play("player");

				break;
			case SDLK_a:
				//std::cout << "a up" << std::endl;
				stateKeyUp = 'a';
				unKey = 1;
					transform->velocity.x = 1;
				if (stateKeyDown == 'a' || stateKeyDown == 'w' || stateKeyDown == 's' || stateKeyDown == 'j')
				{
				transform->velocity.x = 0;
					stopWalk = 1;
				}
				
				if (stateKeyDown == 'd')
				{
				sprite->index = 1;
				stopWalk = 0;
				}
				else
				{
					sprite->index = 0;
				}
				sprite->Play("player");
				break;

			case SDLK_d:
				//std::cout << "d up" << std::endl;
				stateKeyUp = 'd';
				unKey = 1;
					transform->velocity.x = -1;
				if (stateKeyDown == 'd' || stateKeyDown == 'w' || stateKeyDown == 's' || stateKeyDown == 'j')
				{
					transform->velocity.x = 0;

					stopWalk = 1;
				}
				
				if (stateKeyDown == 'a')
				{
				sprite->index = 1;
				
				}
				else
				{
					sprite->index = 0;
				}
				sprite->Play("player");
				break;

			case SDLK_s:
				//std::cout << "s up" << std::endl;
				stateKeyUp = 's';
				unKey = 1;
				transform->velocity.y = 0;
				sprite->index = 0;
				sprite->Play("player");
				break;

			case SDLK_h:
				stateKeyUp = 'h';
				unKey = 1;
				sprite->index = 0;
				sprite->Play("player");
				break;

			case SDLK_j:
				//std::cout << "j up" << std::endl;
				stateKeyUp = 'j';
				unKey = 1;
				sprite->index = 0;
				sprite->hit = 0;
				sprite->Play("player");
				break;

			case SDLK_k:
				stateKeyUp = 'k';
				sprite->index = 0;
				sprite->Play("player");
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;

			default:
				break;
			}
		}
		if (sprite->dead)
		{
			if (sprite->currentFrame == 11)
			{
				sprite->stillDead = 1;
			}
			if (!sprite->stillDead)
			{
			sprite->index = 4;
			sprite->Play("player");
			}
		}
		if (stateKeyUp == 'd' && stateKeyDown == 'a')
		{
			stopWalk = 0;
		}
		if ((stateKeyDown != 'w' && stateKeyDown != 'j' && stateKeyUp == 'w') || (stateKeyDown != 's' && stateKeyDown != 'j' && stateKeyUp == 's') || (stateKeyDown == 'w' && stateKeyUp == 'w') || (stateKeyDown == 's' && stateKeyUp == 's'))
		{
			if (!stopWalk)
			{
			sprite->index = 1;
			sprite->Play("player");
			}
		}
	
	}
};
