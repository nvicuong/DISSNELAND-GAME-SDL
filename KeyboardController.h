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

    //thoi gian tac dung cua thuoc vuong liem
    double vuongLiemTimer = 0;

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
        vuongLiemTimer = 10;
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
            else
            {
                sprite->index = 0;
            }
        }
        else
        {
            sprite->index = 5;
        }
    }

    void update() override
    {
        if (transform->velocity.x != 0 || transform->velocity.y != 0)
        {
            sprite->index = 1;
        }
        else
        {
            sprite->index = 0;
        }
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
            else
            {
                sprite->index = 0;
            }
            completedSlide();

            sprite->Play("player");
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
                    sprite->index = 3;
                    doHit = 1;
                    sprite->Play("player");
                    if (doHit == 1 && (sprite->currentFrame == 5 || sprite->currentFrame == 9) && unHitCheck == 0)
                    {
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

                    break;
                case SDLK_k:
                    if (slideTimer > 1)
                    {
                        sprite->currentFrame = 0;
                        slide = 1;
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
                    else
                    {
                        sprite->index = 0;
                    }
                    sprite->Play("player");

                    break;
                case SDLK_a:
                    if (transform->velocity.x != 0 || transform->velocity.y != 0)
                    {
                        sprite->index = 1;

                    }
                    else
                    {
                        sprite->index = 0;
                    }
                    transform->velocity.x = 0;
                    sprite->Play("player");
                    break;

                case SDLK_d:
                    if (transform->velocity.x != 0 || transform->velocity.y != 0)
                    {
                        sprite->index = 1;
                    }
                    else
                    {
                        sprite->index = 0;
                    }
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
                    else
                    {
                        sprite->index = 0;
                    }
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
                    else
                    {
                        sprite->index = 0;
                    }
                    sprite->Play("player");
                    break;

                case SDLK_ESCAPE:
                    Game::isRunning = false;

                default:
                    break;
                }
            }

            if (!doHit)
            {
                sprite->Play("player");
            }

        }
    }
};
