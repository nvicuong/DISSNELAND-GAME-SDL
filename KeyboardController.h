#pragma once

#include "Game.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	bool hit = 0;
	bool unKey = 0;
	TransformComponent* transform;
	SpriteComponent* sprite;

	//bien kiem tra xem nhan vat co bi gay sat thuong khong
	double hurtedTimer = 0;
	double periodTime = 0;

	//kiem tra qua trinh slide
	bool slide;
	double slideTimer = 1;

	//kiem tra sat thuong len enemy
	bool doHit = 0;
	bool unHit = 0;
	bool unHitCheck = 0;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		hurtedTimer = 1;
		periodTime = SDL_GetTicks() / 1000;
		slide = 0;
		slideTimer = 1;
		doHit = 0;
		unHit = 0;
		unHitCheck = 0;
	}

	void completedSlide()
	{
			if (sprite->currentFrame >= sprite->frames - 1)
			{
				slide = 0;
				slideTimer = 0;
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				/*sprite->index = 1;*/
			}
			else { sprite->index = 5; }
	}

	void update() override
	{
		// std::cout << sprite->index << std::endl;
		if (transform->velocity.x != 0 || transform->velocity.y != 0)
			{
				sprite->index = 1;
			}
			else { sprite->index = 0; }
			// sprite->Play("player");
		//std::cout << "timer: " << sprite->timer << std::endl;
		//std::cout << "currentFrames: " << sprite->currentFrame << std::endl;
		//std::cout << "slide: " << slide << std::endl;
		/*std::cout << "keyDown: " << stateKeyDown << std::endl
		<< "keyUp:     " << stateKeyUp << std::endl << "---------------" << std::endl;*/
		//std::cout << transform->velocity.x << " " << transform->velocity.y << std::endl;
			//std::cout << "currentFrame = " << sprite->currentFrame << std::endl;
		if (hurtedTimer < 0.5 && sprite->dead == 0)
		{
			sprite->index = 2;
			transform->velocity = Vector2D(0, 0);
			sprite->Play("player");
		}
		else if (sprite->dead)
		{
			sprite->index = 4;
			sprite->stillDead = 1;
			sprite->Play("player");
		}
		else if (slide)
		{
			if (transform->velocity.x != 0 || transform->velocity.y != 0)
			{
				sprite->index = 1;
			}
			else { sprite->index = 0; }
			completedSlide();
			
			sprite->Play("player");
			/*transform->velocity.x *= 2;
			transform->velocity.y *= 2;*/
		}
		else
		{
		if (Game::event.type == SDL_KEYDOWN && sprite->dead == 0)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->index = 1;
				sprite->Play("player");
				break;
			case SDLK_a:
				//std::cout << "A" << std::endl;
				transform->velocity.x = -1;
				sprite->index = 1;
				sprite->Play("player");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->index = 1;
				sprite->spriteFlip = SDL_FLIP_NONE;
				sprite->Play("player");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->index = 1;
				sprite->Play("player");
				break;
			case SDLK_j:
				if (unKey == 1)
				{
					sprite->currentFrame = 0;
					unKey = 0;
					sprite->timer = 0;
				}
				//std::cout << "j" << std::endl;
				sprite->index = 3;
				doHit = 1;
				sprite->Play("player");
				//std::cout << "curren: " << sprite->currentFrame << std::endl;
				if (doHit == 1 && (sprite->currentFrame == 5 || sprite->currentFrame == 9) && unHitCheck == 0)
				{
					//std::cout << "...." << sprite->currentFrame << std::endl;
					hit = 1;
					unHit = 0;
					unHitCheck = 1;
				}
				else
				{
					hit = 0;
					unHit = 1;
				}
				if (sprite->currentFrame != 3)
				{
					unHitCheck = 0;
				}
				transform->velocity = Vector2D(0, 0);
				
				//stateKeyUp = 1;
				break;
			case SDLK_k:
				if (slideTimer > 1)
				{
					std::cout << slideTimer;
				sprite->currentFrame = 0;
				slide = 1;
				//slideTimer = 0;
				sprite->index = 5;
				sprite->Play("player");
				}
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
				unKey = 1;
				transform->velocity.y = 0;
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				sprite->Play("player");

				break;
			case SDLK_a:
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				transform->velocity.x = 0;
				sprite->Play("player");
				break;

			case SDLK_d:
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				transform->velocity.x = 0;
				sprite->Play("player");
				break;

			case SDLK_s:
				unKey = 1;
				transform->velocity.y = 0;
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				sprite->Play("player");
				break;

			case SDLK_j:
				unKey = 1;
				sprite->index = 0;
				doHit = 0;
				sprite->Play("player");
				break;

			case SDLK_k:
				if (transform->velocity.x != 0 || transform->velocity.y != 0)
				{
					sprite->index = 1;
				}
				else { sprite->index = 0; }
				sprite->Play("player");
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;

			default:
				break;
			}
		}
		
		if (!doHit)
		{ sprite->Play("player"); }
		
		}
		
	
	}
};
