#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Define.h"

class Menu
{
public:
	
	Menu();
	~Menu();

	void init();
	bool handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static bool isRunning;
	static SDL_Event event;
	/*static AssetManager* assetsMeunu;*/
	SDL_Texture* backgroundText;

private:

};
