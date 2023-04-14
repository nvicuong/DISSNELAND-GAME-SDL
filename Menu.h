#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Define.h"
#include "AssetManager.h"
#include "FontLabel.h"

class Menu
{
public:
	
	Menu();
	~Menu();

	void init();
	bool handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Event event;
	SDL_Texture* backgroundText;

private:

};
