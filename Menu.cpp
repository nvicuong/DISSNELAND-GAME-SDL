#include "Menu.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Components.h"
//Manager managerMenu;
//AssetManager* Game::assets = new AssetManager(&managerMenu);

SDL_Event Menu::event;
bool Menu::isRunning = 1;
void Menu::init()
{
	/*assetsMeunu->AddVector("menu");
	assetsMeunu->AddTexture("menu", "assets/Menu.png");*/

	backgroundText = TextureManager::LoadTexture("assets/menu.png");
	SDL_RenderCopy(Game::renderer, backgroundText, nullptr, nullptr);
}

Menu::Menu()
{}
Menu::~Menu()
{}

bool Menu::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_f)
		{
			isRunning = 0;
		}
		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	return 1;
}

void Menu::render()
{
	/*SDL_RenderClear(Game::renderer);*/
	SDL_RenderPresent(Game::renderer);
}
