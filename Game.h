#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "Define.h"
#include <ctime>
#include <cmath>
// #include "Menu.h"




class ColliderComponent;
class AssetManager;
class Game
{
public:
	static bool isRunningMenu;
	static int openMenu;
	static bool resetGame;
	static int mapCurrent;
	static int enemyRemnants;
	static double periodTimeGame;
	SDL_Texture* barText;
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void initObject1();
	void initObject2();

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	static Mix_Chunk* soundEffects[7];
	static Mix_Music* soundBackground;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupMapBuilding,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupEnemy,
		groupItem
	};

private:
	
	SDL_Window *window;
};