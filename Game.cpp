#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"




Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, MAX_WIDTH_SCREEN, MAX_HEIGHT_SCREEN };

AssetManager* Game::assets = new AssetManager(&manager);

/*[0]IDLE, [1]WALK, [2]HURT, [3]ATTACK, [4]DEAD, [5]SLIDE*/

Animation aniPlayer[] = {
	Animation(IDLE_PLAYER_FRAMES, SPEED, IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT),
	Animation(WALK_PLAYER_FRAMES, SPEED, WALK_PLAYER_WIDTH, WALK_PLAYER_HEIGHT),
	Animation(HURT_PLAYER_FRAMES, SPEED, HURT_PLAYER_WIDTH, HURT_PLAYER_HEIGHT), 
	Animation(ATTACK_PLAYER_FRAMES, ATTACK_SPEED, ATTACK_PLAYER_WIDTH, ATTACK_PLAYER_HEIGHT),
	Animation(DEAD_PLAYER_FRAMES, ATTACK_SPEED, DEAD_PLAYER_WIDTH, DEAD_PLAYER_HEIGHT),
	Animation(SLIDE_PLAYER_FRAMES, SPEED, SLIDE_PLAYER_WIDTH, SLIDE_PLAYER_HEIGHT)
};
int sizeaniPlayer = 6;


//Animation aniProject[] = {
//	Animation(1, 100, 32, 32),
//	Animation(1, 100, 32, 32)
//};
//int sizeaniProject = 2;


Animation aniEnemy1[] = {
	Animation(IDLE_ENEMY1_FRAMES, SPEED, IDLE_ENEMY1_WIDTH, IDLE_ENEMY1_HEIGHT),
	Animation(IDLE_ENEMY1_FRAMES, SPEED, IDLE_ENEMY1_WIDTH, IDLE_ENEMY1_HEIGHT),
	Animation(HURT_ENEMY1_FRAMES, SPEED, HURT_ENEMY1_WIDTH, HURT_ENEMY1_HEIGHT),
	Animation(ATTACK_ENEMY1_FRAMES, SPEED, ATTACK_ENEMY1_WIDTH, ATTACK_ENEMY1_HEIGHT),
	Animation(DEATH_ENEMY1_FRAMES, SPEED, DEATH_ENEMY1_WIDTH, DEATH_ENEMY1_HEIGHT),
};
int sizeaniEnemy1 = 5;

Animation aniEnemy2[] = {
	Animation(IDLE_ENEMY2_FRAMES, SPEED, IDLE_ENEMY2_WIDTH, IDLE_ENEMY2_HEIGHT),
	Animation(WALK_ENEMY2_FRAMES, SPEED, WALK_ENEMY2_WIDTH, WALK_ENEMY2_HEIGHT),
	Animation(HURT_ENEMY2_FRAMES, SPEED, HURT_ENEMY2_WIDTH, HURT_ENEMY2_HEIGHT),
	Animation(ATTACK_ENEMY2_FRAMES, ATTACK_SPEED, ATTACK_ENEMY2_WIDTH, ATTACK_ENEMY2_HEIGHT),
	Animation(DEATH_ENEMY2_FRAMES, SPEED, DEATH_ENEMY2_WIDTH, DEATH_ENEMY2_HEIGHT),
};
int sizeaniEnemy2 = 5;


bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy1(manager.addEntity());



double deltaTime(double& periodTime)
{
	double latterTime = SDL_GetTicks()/1000;
	double delta = latterTime - periodTime;
	periodTime = latterTime;
	return delta;

}


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	assets->AddVector("terrain");
	//assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("terrain", "assets/tilemap_packed.png");


	assets->AddVector("player");
	assets->AddTexture("player", "assets/player/IdlePlayer22x35_6frames.png");
	assets->AddTexture("player", "assets/player/RunPlayer35x30_8frames.png");
	assets->AddTexture("player", "assets/player/HurtPlayer25x32_4frames.png");
	assets->AddTexture("player", "assets/player/AttackPlayer60x45_12frames.png");
	assets->AddTexture("player", "assets/player/DeathPlayer45x45_11frames.png");
	assets->AddTexture("player", "assets/player/SlidePlayer40x28_5frames.png");

	assets->AddVector("enemy1");
	assets->AddTexture("enemy1", "assets/MonstersEnemies/Flying eye/IdleEnemy1_45x35_8frames.png");
	assets->AddTexture("enemy1", "assets/MonstersEnemies/Flying eye/IdleEnemy1_45x35_8frames.png");
	assets->AddTexture("enemy1", "assets/MonstersEnemies/Flying eye/HurtEnemy1_45x35_4frames.png");
	assets->AddTexture("enemy1", "assets/MonstersEnemies/Flying eye/AttackEnemy1_45x35_8frames.png");
	assets->AddTexture("enemy1", "assets/MonstersEnemies/Flying eye/DeathEnemy1_60x35_4frames.png");

	assets->AddVector("enemy2");
	assets->AddTexture("enemy2", "assets/MonstersEnemies/Skeleton/IdleEnemy2_50x53_4frames.png");
	assets->AddTexture("enemy2", "assets/MonstersEnemies/Skeleton/WalkEnemy2_50x53_4frames.png");
	assets->AddTexture("enemy2", "assets/MonstersEnemies/Skeleton/HurtEnemy2_50x53_4frames.png");
	assets->AddTexture("enemy2", "assets/MonstersEnemies/Skeleton/Attack_Enemy2_80x60_8frames.png");
	assets->AddTexture("enemy2", "assets/MonstersEnemies/Skeleton/DeathEnemy2_60x53_4frames.png");



	assets->AddVector("projectile");
	assets->AddTexture("projectile", "assets/1_Magic/6_0.png");


	map = new Map("terrain", 3, 16);

	map->LoadMap("assets/tilemap.map", 50, 20);
	map->sizeWidthMap = 50 * map->scaledSize - MAX_WIDTH_SCREEN;
	map->sizeHeightMap = 20 * map->scaledSize - MAX_HEIGHT_SCREEN;
	camera.w = map->sizeWidthMap;
	camera.h = map->sizeHeightMap;


	player.addComponent<TransformComponent>(800, 500, ATTACK_PLAYER_HEIGHT, ATTACK_PLAYER_WIDTH, 1);
	player.addComponent<SpriteComponent>("player", aniPlayer, sizeaniPlayer);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<StatusBar>(100, 100, IDLE_PLAYER_WIDTH);
	player.addGroup(groupPlayers);

	/*enemy1.addComponent<TransformComponent>(600, 640, IDLE_PLAYER_HEIGHT, IDLE_PLAYER_WIDTH, 1);
	enemy1.addComponent<SpriteComponent>("enemy1", aniEnemy1, sizeaniEnemy1);
	enemy1.addComponent<Enemy1>(1);
	enemy1.addComponent<ColliderComponent>("enemy1");
	enemy1.addGroup(groupEnemy);*/

	assets->CreateEnemy1(Vector2D(600, 640), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);
	assets->CreateEnemy1(Vector2D(800, 800), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);


	assets->CreateEnemy2(Vector2D(600,640), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	assets->CreateEnemy2(Vector2D(900, 800), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	assets->CreateEnemy2(Vector2D(800, 800), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);

	//assets->CreateProJectile(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	/*assets->CreateProJectile(Vector2D(600, 620), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	assets->CreateProJectile(Vector2D(400, 600), Vector2D(2, 1), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	assets->CreateProJectile(Vector2D(600, 600), Vector2D(2, -1), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);*/

	//assets->CreateEnemy1(Vector2D(600, 600), Vector2D(0, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 1000, 2, "enemy1", 0, aniEnemy1, sizeaniEnemy1);
	/*assets->CreateEnemy1(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "enemy1", 0, aniProject, sizeaniProject);
	assets->CreateEnemy1(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "enemy1", 0, aniProject, sizeaniProject);*/

	

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& enemies(manager.getGroup(Game::groupEnemy));
void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


//double periodTime1 = SDL_GetTicks()/1000;
//double periodTime2 = SDL_GetTicks()/1000;
//double timer1 = 0;
//double timer2 = 0;
//bool attacked = 0;
//bool check = 0;
void Game::update()
{

	

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, cCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
			//std::cout << "width: " << playerCol.w << "  height: " << playerCol.h << std::endl;
		}
	}

		/*timer1 += deltaTime(periodTime1);*/
	for (auto& e : enemies)
	{
		SDL_Rect eCol = e->getComponent<ColliderComponent>().collider;
		//std::cout << e->getComponent<ColliderComponent>().tag << std::endl;
		std::string s = e->getComponent<ColliderComponent>().tag;
		std::cout << s << " timer: " << e->getComponent<Enemy1>().timer << std::endl;
		if (s == "enemy1")
		{
			e->getComponent<Enemy1>().timer += deltaTime(e->getComponent<Enemy1>().periodTime);
			if (player.getComponent<SpriteComponent>().dead == 0)
			{
				if (e->getComponent<Enemy1>().timer > 2)
				{
					e->getComponent<Enemy1>().fireGun(eCol, playerCol, assets);
					e->getComponent<Enemy1>().timer = 0;
				}
			}
		}
		if (s == "enemy2")
		{
			if (player.getComponent<SpriteComponent>().dead == 0)
			{
				//std::cout << "timer2: " << timer2 << std::endl;
				e->getComponent<Enemy1>().attackPlayer(eCol, playerCol, e->getComponent<Enemy1>().attacked);
				if (e->getComponent<Enemy1>().timer > 5)
				{
					e->getComponent<Enemy1>().attacked = 0;
				if (e->getComponent<SpriteComponent>().index == 3 &&
					e->getComponent<Enemy1>().hit == 1
					)
				{
					std::cout << "dam trung" << std::endl;
					//player.getComponent<StatusBar>().health -= 20;
					e->getComponent<Enemy1>().hit = 0;
					std::cout << "playerHealth: " << player.getComponent<StatusBar>().health << std::endl;
					
					e->getComponent<Enemy1>().check = 1;
					e->getComponent<Enemy1>().timer = 0;
					//std::cout << "health: " << player.getComponent<StatusBar>().health << std::endl;
					//std::cout << "check timer2: " << timer2 << std::endl;
				}
				}
				else
				{
					e->getComponent<Enemy1>().timer += deltaTime(e->getComponent<Enemy1>().periodTime);
					//std::cout << "timer2: " << timer2 << std::endl;
					if (e->getComponent<Enemy1>().check)
					{
						e->getComponent<Enemy1>().attacked = 1;
						//check = 0;

					}
					else
					{
						e->getComponent<Enemy1>().attacked = 0;
					}
					//std::cout << "attaked: " << attacked << std::endl;
				}
			}
		}
		/*if (e == *(enemies.end() - 1) && e->getComponent<Enemy1>().timer > 2)
			{
			e->getComponent<Enemy1>().timer = 0;
			}*/
		if (Collision::AABB(playerCol, eCol))
		{
			//player.getComponent<TransformComponent>().position = playerPos;
			if ((player.getComponent<SpriteComponent>().index == 3) &&
				player.getComponent<KeyboardController>().hit == 1)
			{
				e->getComponent<SpriteComponent>().index = 2;

				e->getComponent<StatusBar>().health -= 50;
				player.getComponent<KeyboardController>().hit = 0;
				//std::cout << e->getComponent<ColliderComponent>().tag << "Heath: " << e->getComponent<StatusBar>().health << std::endl;
			}
			if (e->getComponent<StatusBar>().health <= 0)
			{
				e->destroy();
			}
		}
		
	}


		
	for (int i = 0; i < projectiles.size(); i++)
	{
		//std::cout << projectiles.size() << " ";
		auto& p = projectiles[i];
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			if (player.getComponent<SpriteComponent>().index != 2)
			{
			player.getComponent<StatusBar>().getDamage(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider);
			}
			//std::cout << "health: " << player.getComponent<StatusBar>().health << std::endl;
			p->destroy();
		}
	}
			if (player.getComponent<StatusBar>().health <= 0)
			{
				player.getComponent<SpriteComponent>().dead = 1;
				player.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
			}

	camera.x = player.getComponent<TransformComponent>().position.x - MAX_WIDTH_SCREEN/2;
	camera.y = player.getComponent<TransformComponent>().position.y - MAX_HEIGHT_SCREEN/2;


	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

	/*std::cout << player.getComponent<SpriteComponent>().wi*/

}



void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
