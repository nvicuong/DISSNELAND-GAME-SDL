#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "FontLabel.h"
#include <sstream>




Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
TTF_Font* font = NULL;

bool Game::isRunningMenu = 1;
int Game::openMenu = 1;
bool Game::resetGame = 0;
int Game::mapCurrent = 1;
int Game::enemyRemnants = 0;


SDL_Rect destBarText = {0, 0, 1000, 100};
SDL_Rect Game::camera = { 0, 0, MAX_WIDTH_SCREEN, MAX_HEIGHT_SCREEN };

AssetManager* Game::assets = new AssetManager(&manager);

/*[0]IDLE, [1]WALK, [2]HURT, [3]ATTACK, [4]DEAD, [5]SLIDE*/

Animation aniPlayer[] = {
	Animation(IDLE_PLAYER_FRAMES, SPEED, IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT),
	Animation(WALK_PLAYER_FRAMES, SPEED, WALK_PLAYER_WIDTH, WALK_PLAYER_HEIGHT),
	Animation(HURT_PLAYER_FRAMES, SPEED, HURT_PLAYER_WIDTH, HURT_PLAYER_HEIGHT), 
	Animation(ATTACK_PLAYER_FRAMES, ATTACK_SPEED, ATTACK_PLAYER_WIDTH, ATTACK_PLAYER_HEIGHT),
	Animation(DEAD_PLAYER_FRAMES, ATTACK_SPEED, DEAD_PLAYER_WIDTH, DEAD_PLAYER_HEIGHT),
	Animation(SLIDE_PLAYER_FRAMES, SLIDE_PLAYER_SPEED, SLIDE_PLAYER_WIDTH, SLIDE_PLAYER_HEIGHT)
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
	Animation(DEATH_ENEMY1_FRAMES, SPEED_DEATH_ENEMY, DEATH_ENEMY1_WIDTH, DEATH_ENEMY1_HEIGHT),
};
int sizeaniEnemy1 = 5;

Animation aniEnemy2[] = {
	Animation(IDLE_ENEMY2_FRAMES, SPEED, IDLE_ENEMY2_WIDTH, IDLE_ENEMY2_HEIGHT),
	Animation(WALK_ENEMY2_FRAMES, SPEED, WALK_ENEMY2_WIDTH, WALK_ENEMY2_HEIGHT),
	Animation(HURT_ENEMY2_FRAMES, SPEED, HURT_ENEMY2_WIDTH, HURT_ENEMY2_HEIGHT),
	Animation(ATTACK_ENEMY2_FRAMES, ATTACK_SPEED, ATTACK_ENEMY2_WIDTH, ATTACK_ENEMY2_HEIGHT),
	Animation(DEATH_ENEMY2_FRAMES, SPEED_DEATH_ENEMY, DEATH_ENEMY2_WIDTH, DEATH_ENEMY2_HEIGHT),
};
int sizeaniEnemy2 = 5;

Animation aniBoss[] = {
	Animation(IDLE_BOSS_FRAMES, SPEED, IDLE_BOSS_WIDTH, IDLE_BOSS_HEIGHT),
	Animation(WALK_BOSS_FRAMES, SPEED, WALK_BOSS_WIDTH, WALK_BOSS_HEIGHT),
	Animation(HURT_BOSS_FRAMES, SPEED, HURT_BOSS_WIDTH, HURT_BOSS_HEIGHT),
	Animation(ATTACK_BOSS_FRAMES, ATTACK_SPEED, ATTACK_BOSS_WIDTH, ATTACK_BOSS_HEIGHT),
	Animation(RUN_BOSS_FRAMES, SPEED, RUN_BOSS_WIDTH, RUN_BOOS_HEIGHT),
};
int sizeaniBoss = 5;





bool Game::isRunning = false;

auto& player(manager.addEntity());
// auto& enemy1(manager.addEntity());
// auto& label(manager.addEntity());

FontLabel timeGame(MAX_WIDTH_SCREEN - 100, 20, "TIME");
FontLabel enemyRemain(MAX_WIDTH_SCREEN - 300, 20, "REMAINING MONSTERS");
FontLabel giangHoa(200, 20, "PRESS E TO GIANG HOA");
FontLabel thuocKimCuong(MAX_WIDTH_SCREEN - 300, 50, "ABSORB THUOC KIM CUONG");
FontLabel thuocVuongLiem(MAX_WIDTH_SCREEN - 300, 80, "ABSORB THUOC VUONG LIEM");




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
			SDL_SetRenderDrawColor(renderer, 255, 127, 39, 255);
		}

		isRunning = true;
	}


	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	font = TTF_OpenFont("assets/arial.ttf", 16);
	// assets->AddFont("arial", "assets/arial.ttf", 16);
	// timeGame.setColor(1);
	timeGame.SetlabelText(font);
	timeGame.setColor(FontLabel::WHITE_TEXT);

	enemyRemain.SetlabelText(font);
	enemyRemain.setColor(FontLabel::WHITE_TEXT);

	giangHoa.SetlabelText(font);
	giangHoa.setColor(FontLabel::PINK_TEXT);

	thuocKimCuong.SetlabelText(font);
	thuocKimCuong.setColor(FontLabel::WHITE_TEXT);

	thuocVuongLiem.SetlabelText(font);
	thuocVuongLiem.setColor(FontLabel::WHITE_TEXT);



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

	assets->AddVector("boss");
	assets->AddTexture("boss", "assets/MonstersEnemies/Boss/idle_53x42_5frames.png");
	assets->AddTexture("boss", "assets/MonstersEnemies/Boss/walk_53x42_4frames.png");
	assets->AddTexture("boss", "assets/MonstersEnemies/Boss/hurt_53x42_3frames.png");
	assets->AddTexture("boss", "assets/MonstersEnemies/Boss/attack_75x80_9frames.png");
	assets->AddTexture("boss", "assets/MonstersEnemies/Boss/run_53x42_4frames.png");

	assets->AddVector("item");
	assets->AddTexture("item", "assets/Item/thuocKimCuong.png");
	assets->AddTexture("item", "assets/Item/thuocVuongLiem.png");


	assets->AddVector("projectile");
	assets->AddTexture("projectile", "assets/1_Magic/6_0.png");


	map = new Map("terrain", 3, 16);

	// map->LoadMap("assets/tilemap_1.map", 50, 20);
	
	map->sizeWidthMap = 50 * map->scaledSize - MAX_WIDTH_SCREEN;
	map->sizeHeightMap = 20 * map->scaledSize - MAX_HEIGHT_SCREEN;
	camera.w = map->sizeWidthMap;
	camera.h = map->sizeHeightMap;


	player.addComponent<TransformComponent>(800, 500, ATTACK_PLAYER_HEIGHT, ATTACK_PLAYER_WIDTH, 1);
	player.addComponent<SpriteComponent>("player", aniPlayer, sizeaniPlayer);
	player.addComponent<KeyboardController>();
	player.addComponent<StatusBar>(100, 100, IDLE_PLAYER_WIDTH, "player");
	player.addGroup(groupPlayers);

	// assets->CreateEnemy1(Vector2D(600, 640), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);
	// assets->CreateEnemy1(Vector2D(800, 800), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);


	// assets->CreateEnemy2(Vector2D(600,640), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateEnemy2(Vector2D(900, 800), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateEnemy2(Vector2D(800, 800), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);

	// enemyRemnants = 5;

	//assets->CreateProJectile(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	/*assets->CreateProJectile(Vector2D(600, 620), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	assets->CreateProJectile(Vector2D(400, 600), Vector2D(2, 1), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);
	assets->CreateProJectile(Vector2D(600, 600), Vector2D(2, -1), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "projectile", 0, aniProject, sizeaniProject);*/

	//assets->CreateEnemy1(Vector2D(600, 600), Vector2D(0, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 1000, 2, "enemy1", 0, aniEnemy1, sizeaniEnemy1);
	/*assets->CreateEnemy1(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "enemy1", 0, aniProject, sizeaniProject);
	assets->CreateEnemy1(Vector2D(600, 600), Vector2D(2, 0), OBJECT_WIDTH, OBJECT_HEIGHT, 200, 2, "enemy1", 0, aniProject, sizeaniProject);*/

	

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& building(manager.getGroup(Game::groupMapBuilding));
auto& colliders(manager.getGroup(Game::groupColliders));


auto& players(manager.getGroup(Game::groupPlayers));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& enemies(manager.getGroup(Game::groupEnemy));

auto& items(manager.getGroup(Game::groupItem));
double giangHoaTime = 0;
bool checkGiangHoa = 0;
bool checkPossibleGiangHoa = 0;
void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_p)
        {
            isRunningMenu = 1;
			openMenu = 2;
        }
	if (event.key.keysym.sym == SDLK_e)
	{
		if (checkPossibleGiangHoa)
		{
			checkGiangHoa = 1;
			giangHoaTime = 0;
			std::cout << "gianghoa" << std::endl;
		}
	}
	break;
	case SDL_QUIT:
	isRunning = 0;
	break;
	// std::cout << "quit";
	// 	isRunningMenu = 1;
	// 	openMenu = 2;
	default:
		break;
	}
}


double Game::periodTimeGame = SDL_GetTicks()/1000;
//double periodTime2 = SDL_GetTicks()/1000;
double countTimeGame = 0;
double nextMaPtime = 0;
int fired = 0;

bool checkThuocKimCuong = 0;
bool checkThuocVuongLiem = 0;
void Game::update()
{

	srand(time(NULL));

	double delta = deltaTime(periodTimeGame);

	countTimeGame += delta;
	nextMaPtime += delta;
	giangHoaTime += delta;

	if (static_cast<int>(countTimeGame) % 10 == 0)
	{
		checkThuocKimCuong = 0;
		checkThuocVuongLiem = 0;
	}
	
	if (mapCurrent == 2 && player.getComponent<StatusBar>().health <= 100)
	{
		checkPossibleGiangHoa = 1;
	}
	else
	{
		checkPossibleGiangHoa = 0;
	}

	SDL_Rect playerCol = player.getComponent<SpriteComponent>().posRect;
	// SDL_Rect playerCol = {player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y, player.getComponent<TransformComponent>().width, player.getComponent<TransformComponent>().height};
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	double dlTPlayer = deltaTime(player.getComponent<KeyboardController>().periodTime);
	player.getComponent<KeyboardController>().hurtedTimer += dlTPlayer;
	player.getComponent<KeyboardController>().slideTimer += dlTPlayer;
	player.getComponent<KeyboardController>().vuongLiemTimer += dlTPlayer;

	timeGame.destroy();
	enemyRemain.destroy();

	timeGame.SetlabelText(font);
	enemyRemain.SetlabelText(font);

	std::stringstream ss1, ss2;
	ss1 << "TIME: " << static_cast<int>(countTimeGame);
	
	// label.getComponent<FontLabel>().SetlabelText("sdll", "arial");
	timeGame.SetText(ss1.str());
	ss2 << "MONSTER: " << enemyRemnants;
	enemyRemain.SetText(ss2.str());
	// timeGame.GetColor();

	manager.refresh();
	manager.update();

	if (enemyRemnants == 0 && nextMaPtime >= 5)
	{
		Game::resetGame = 1;
		Game::mapCurrent = 2;
	}
	

		/*timer1 += deltaTime(periodTime1);*/
	for (auto& e : enemies)
	{
		// SDL_Rect eCol = e->getComponent<SpriteComponent>().posRect;
	
		std::string s = e->getComponent<SpriteComponent>().tag;
		//std::cout << s << " timer: " << e->getComponent<Enemy1>().timer << std::endl;
		double dlT = deltaTime(e->getComponent<Enemy1>().periodTime);
		e->getComponent<Enemy1>().hurtedTimer += dlT;
			e->getComponent<Enemy1>().timer += dlT;
		//std::cout << e->getComponent<Enemy1>().hurtedTimer << std::endl;
		//std::cout << "index: " << e->getComponent<SpriteComponent>().index << std::endl;
		if (e->getComponent<Enemy1>().hurtedTimer < 1.5)
		{
			if (e->getComponent<StatusBar>().health <= 0)
			{
				if (e->getComponent<SpriteComponent>().stillDead == 0)
				{
				int ranDrop = rand() % (1 - 0 + 1) + 0;
				if (ranDrop)
				{
				int ran = rand() % (1 - 0 + 1) + 0;
				e->getComponent<Enemy1>().dropDrug(assets, ran);
				}
				}
				e->getComponent<SpriteComponent>().index = 4;
				e->getComponent<SpriteComponent>().stillDead = 1;
				e->getComponent<SpriteComponent>().Play(s);
				// e->getComponent<Enemy1>().getDeath();
				if (e->getComponent<Enemy1>().hurtedTimer >= 1)
				{
				e->destroy();
				enemyRemnants -= 1;
				if (enemyRemnants == 0)
				{
					nextMaPtime = 0;
				}
				}
			}
			else
			{
			e->getComponent<Enemy1>().getHurt();
			}
		}
		else
		{
			e->getComponent<Enemy1>().unHurted = 0;
		if (s == "enemy1")
		{
			e->getComponent<Enemy1>().walkAround();
			e->getComponent<SpriteComponent>().index = 0;
			e->getComponent<SpriteComponent>().Play(s);
			if (e->getComponent<Enemy1>().checkHurted)
			{
			e->getComponent<TransformComponent>().velocity.x = -1;
			e->getComponent<Enemy1>().checkHurted = 0;
			}

			if (player.getComponent<SpriteComponent>().dead == 0)
			{
				if (e->getComponent<Enemy1>().timer > 2)
				{
					e->getComponent<Enemy1>().fireGun(e->getComponent<SpriteComponent>().posRect, playerCol, assets);
					e->getComponent<Enemy1>().timer = 0;
				}
			}
		}
		if (s == "enemy2")
		{
			if (player.getComponent<SpriteComponent>().dead == 0)
			{
				//std::cout << "timer2: " << timer2 << std::endl;
				e->getComponent<Enemy1>().attackPlayer(e->getComponent<SpriteComponent>().posRect, playerCol);
				//std::cout << "hit: " << e->getComponent<Enemy1>().hit << "  index: " << e->getComponent<SpriteComponent>().index << std::endl;
				if (e->getComponent<Enemy1>().hit && e->getComponent<Enemy1>().attacked && player.getComponent<SpriteComponent>().index != 5)
				{
					// std::cout << "dam trung" << std::endl;
					
					player.getComponent<StatusBar>().health -= 10;
					player.getComponent<KeyboardController>().hurtedTimer = 0;
					e->getComponent<Enemy1>().hit = 0;
					
					//std::cout << "playerHealth: " << player.getComponent<StatusBar>().health << std::endl;
					
					//e->getComponent<Enemy1>().check = 1;
					e->getComponent<Enemy1>().timer = 0;
					//std::cout << "health: " << player.getComponent<StatusBar>().health << std::endl;
					//std::cout << "check timer2: " << timer2 << std::endl;
				}
				else
				{
					e->getComponent<Enemy1>().timer += deltaTime(e->getComponent<Enemy1>().periodTime);
					
				}
			}
		}
		if (s == "boss")
		{
			if (player.getComponent<SpriteComponent>().dead == 0)
			{
				//std::cout << "timer2: " << timer2 << std::endl;

				int timeFireGun = static_cast<int>(e->getComponent<Enemy1>().timer);
				if (timeFireGun % 10 == 0 && fired != timeFireGun && timeFireGun != 0)
				{
					e->getComponent<Enemy1>().fireGunCircle(e->getComponent<SpriteComponent>().posRect, playerCol, assets);
					fired = timeFireGun;
				}

				e->getComponent<Enemy1>().attackPlayer(e->getComponent<SpriteComponent>().posRect, playerCol);
				//std::cout << "hit: " << e->getComponent<Enemy1>().hit << "  index: " << e->getComponent<SpriteComponent>().index << std::endl;
				if (e->getComponent<Enemy1>().hit && e->getComponent<Enemy1>().attacked && player.getComponent<SpriteComponent>().index != 5)
				{
					// std::cout << "dam trung" << std::endl;
					
					player.getComponent<StatusBar>().health -= 10;
					player.getComponent<KeyboardController>().hurtedTimer = 0;
					e->getComponent<Enemy1>().hit = 0;
					
					//std::cout << "playerHealth: " << player.getComponent<StatusBar>().health << std::endl;
					
					//e->getComponent<Enemy1>().check = 1;
					e->getComponent<Enemy1>().timer = 0;
					//std::cout << "health: " << player.getComponent<StatusBar>().health << std::endl;
					//std::cout << "check timer2: " << timer2 << std::endl;
				}
				else
				{
					e->getComponent<Enemy1>().timer += deltaTime(e->getComponent<Enemy1>().periodTime);
				}
			}
		}

		}
		/*if (e == *(enemies.end() - 1) && e->getComponent<Enemy1>().timer > 2)
			{
			e->getComponent<Enemy1>().timer = 0;
			}*/
		
		if (Collision::AABB(playerCol, e->getComponent<SpriteComponent>().posRect))
		{
			e->getComponent<Enemy1>().xpos = 0;
			e->getComponent<Enemy1>().ypos = 0;
			//player.getComponent<TransformComponent>().position = playerPos;
			if ((player.getComponent<SpriteComponent>().index == 3) &&
				player.getComponent<KeyboardController>().hit == 1)
			{
				if (player.getComponent<KeyboardController>().vuongLiemTimer < 10)
				{
					e->getComponent<StatusBar>().health -= 20;
				}
				else
				{
					e->getComponent<StatusBar>().health -= 10;
				}
				if (e->getComponent<Enemy1>().unHurted == 0)
				{
					e->getComponent<Enemy1>().hurtedTimer = 0;
					e->getComponent<Enemy1>().unHurted = 1;
				}
				e->getComponent<Enemy1>().checkHurted = 1;
				player.getComponent<KeyboardController>().hit = 0;
				//std::cout << e->getComponent<ColliderComponent>().tag << "Heath: " << e->getComponent<StatusBar>().health << std::endl;
			}
			
		}
		
	}


		
	for (int i = 0; i < projectiles.size(); i++)
	{
		//std::cout << projectiles.size() << " ";
		auto& p = projectiles[i];
		if (Collision::AABB(player.getComponent<SpriteComponent>().posRect, p->getComponent<SpriteComponent>().posRect))
		{
			if (player.getComponent<SpriteComponent>().index != 5)
			{
			player.getComponent<StatusBar>().getDamage(player.getComponent<SpriteComponent>().posRect, p->getComponent<SpriteComponent>().posRect);
			player.getComponent<KeyboardController>().hurtedTimer = 0;
			p->destroy();
			}
			//std::cout << "health: " << player.getComponent<StatusBar>().health << std::endl;
		}
	}
			if (player.getComponent<StatusBar>().health <= 0)
			{
				player.getComponent<SpriteComponent>().dead = 1;
				player.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
				player.getComponent<SpriteComponent>().index = 4;
			}
			if (player.getComponent<SpriteComponent>().dead)
			{
				if (player.getComponent<KeyboardController>().hurtedTimer > 5)
				{
				countTimeGame = 0;
				isRunningMenu = 1;
				openMenu = 0;
				}
			}

		for (auto& c : colliders)
	{
		if (Collision::AABB(playerCol, c->getComponent<ColliderComponent>().collider))
		{
			player.getComponent<TransformComponent>().position = playerPos;
			//std::cout << "width: " << playerCol.w << "  height: " << playerCol.h << std::endl;
		}
		for (auto& p : projectiles)
		{
			if (Collision::AABB(p->getComponent<SpriteComponent>().posRect, c->getComponent<ColliderComponent>().collider))
		{
			p->destroy();
		}
		}
	}

	for (auto& i : items)
	{
		if (Collision::AABB(playerCol, i->getComponent<SpriteComponent>().posRect) && i->getComponent<Item>().check())
		{
			if (i->getComponent<Item>().getIndex() == 0)
			{
				checkThuocKimCuong = 1;
				player.getComponent<StatusBar>().health = 100;
			}
			if (i->getComponent<Item>().getIndex() == 1)
			{
				checkThuocVuongLiem = 1;
				player.getComponent<KeyboardController>().vuongLiemTimer = 0;
			}
			i->destroy();
			//std::cout << "width: " << playerCol.w << "  height: " << playerCol.h << std::endl;
		}
	}



	float newXposCam;
	float newYposCam;

	if (player.getComponent<KeyboardController>().hurtedTimer < 0.5)
	{
		newXposCam = player.getComponent<TransformComponent>().position.x - MAX_WIDTH_SCREEN/2 + 50*sin(SDL_GetTicks()/100);
		newYposCam = player.getComponent<TransformComponent>().position.y - MAX_HEIGHT_SCREEN/2 + 50*sin(SDL_GetTicks()/100);
	}
	else
	{
		newXposCam = player.getComponent<TransformComponent>().position.x - MAX_WIDTH_SCREEN/2;
		newYposCam = player.getComponent<TransformComponent>().position.y - MAX_HEIGHT_SCREEN/2;
	}

	camera.x = camera.x + (newXposCam - camera.x) * SMOOTHING_FACTOR;
	camera.y = camera.y + (newYposCam - camera.y) * SMOOTHING_FACTOR;

	// camera.x = player.getComponent<TransformComponent>().position.x - MAX_WIDTH_SCREEN/2;
	// camera.y = player.getComponent<TransformComponent>().position.y - MAX_HEIGHT_SCREEN/2;


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

	if (checkGiangHoa)
	{
		SDL_DestroyTexture(barText);
		barText = NULL;
		barText = TextureManager::LoadTexture("assets/giangHoa.png");
		SDL_RenderCopy(renderer, barText, NULL, NULL);
		if (giangHoaTime >= 5)
		{
			countTimeGame = 0;
			isRunningMenu = 1;
			openMenu = 0;
		}
		std::cout << "dang giang hoa" << std::endl;
	}
	else
	{
	SDL_DestroyTexture(barText);
	barText = NULL;
	
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

	for (auto& d : building)
	{
		d->draw();
	}
	
	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& i : items)
	{
		i->draw();
	}

	barText = TextureManager::LoadTexture("assets/bar.png");
	SDL_RenderCopy(renderer, barText, NULL, &destBarText);
	player.getComponent<StatusBar>().draw();
	timeGame.draw();
	enemyRemain.draw();
	if (checkPossibleGiangHoa)
	{
		giangHoa.draw();
	}
	if (checkThuocKimCuong)
	{ thuocKimCuong.draw(); }
	if (checkThuocVuongLiem)
	{ thuocVuongLiem.draw(); }
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::initObject1()
{

	// for (auto e : enemies)
	// {
	// 	e->destroy();
	// }
	enemies.clear();
	tiles.clear();
	building.clear();
	colliders.clear();
	items.clear();

	// for (auto i : items)
	// {
	// 	i->destroy();
	// }

	map->LoadMap("assets/tilemap_1.map", 50, 20);

	assets->CreateEnemy1(Vector2D(600, 640), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);
	assets->CreateEnemy1(Vector2D(800, 800), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);


	assets->CreateEnemy2(Vector2D(14*48,7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateThuoc(Vector2D(15*48, 7*48), 16, 16, "item", aniItem, sizeItem, 0);
	// assets->CreateEnemy2(Vector2D(16*48, 7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateEnemy2(Vector2D(18*48, 7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);

	// assets->CreateBoss(Vector2D(15*48, 7*48), IDLE_BOSS_WIDTH, IDLE_BOSS_HEIGHT, "boss", aniBoss, sizeaniBoss);

	player.getComponent<SpriteComponent>().dead = 0;
	player.getComponent<SpriteComponent>().stillDead = 0;
	player.getComponent<StatusBar>().health = 100;
	player.getComponent<TransformComponent>().position = Vector2D(17*48, 7*48);
	player.getComponent<SpriteComponent>().index = 0;
	player.getComponent<SpriteComponent>().Play("player");

	enemyRemnants = 3;

	resetGame = 0;
}

void Game::initObject2()
{

	// for (auto e : enemies)
	// {
	// 	e->destroy();
	// }

	enemies.clear();
	tiles.clear();
	building.clear();
	colliders.clear();
	items.clear();

	// for (auto i : items)
	// {
	// 	i->destroy();
	// }


	map->LoadMap("assets/tilemap_2.map", 50, 20);

	assets->CreateEnemy1(Vector2D(600, 640), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);
	assets->CreateEnemy1(Vector2D(800, 800), 40, 30, "enemy1", aniEnemy1, sizeaniEnemy1);


	// assets->CreateEnemy2(Vector2D(14*48,7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateEnemy2(Vector2D(16*48, 7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);
	// assets->CreateEnemy2(Vector2D(18*48, 7*48), IDLE_PLAYER_WIDTH, IDLE_PLAYER_HEIGHT, "enemy2", aniEnemy2, sizeaniEnemy2);

	assets->CreateBoss(Vector2D(15*48, 7*48), IDLE_BOSS_WIDTH, IDLE_BOSS_HEIGHT, "boss", aniBoss, sizeaniBoss);
	player.getComponent<SpriteComponent>().dead = 0;
	player.getComponent<SpriteComponent>().stillDead = 0;
	player.getComponent<StatusBar>().health = 100;
	player.getComponent<TransformComponent>().position = Vector2D(17*48, 7*48);
	player.getComponent<SpriteComponent>().index = 0;
	player.getComponent<SpriteComponent>().Play("player");

	enemyRemnants = 3;

	resetGame = 0;
}
