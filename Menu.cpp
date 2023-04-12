#include "Menu.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Components.h"
#include <sstream>
Manager managerMenu;
AssetManager* assetsMenu = new AssetManager(&managerMenu);

SDL_Event Menu::event;
bool Menu::isRunning = 1;
auto& start(managerMenu.addEntity());
auto& tutorial(managerMenu.addEntity());
auto& setting(managerMenu.addEntity());
void Menu::init()
{
	/*assetsMeunu->AddVector("menu");
	assetsMeunu->AddTexture("menu", "assets/Menu.png");*/

	backgroundText = TextureManager::LoadTexture("assets/menu.png");

	assetsMenu->AddFont("arial", "assets/arial.ttf", 32);
	SDL_Color WHITE = {255, 255, 255, 255};
	start.addComponent<FontLabel>(20, 20, "START", "arial", WHITE);
	tutorial.addComponent<FontLabel>(30, 30, "TUTORIAL", "arial", WHITE);
	setting.addComponent<FontLabel>(40, 40, "SETTING", "arial",  WHITE);
	SDL_RenderCopy(Game::renderer, backgroundText, nullptr, nullptr);
}

Menu::Menu()
{}
Menu::~Menu()
{}

bool Menu::handleEvents()
{

	SDL_PollEvent(&event);

	std::stringstream ss; // initialize ss outside the switch statement
switch (event.type)
{
	case SDL_MOUSEMOTION:
		ss.str(""); // reset ss for each label
		ss << "mouse position: " << event.motion.x << " , " << event.motion.y;
		start.getComponent<FontLabel>().SetlabelText(ss.str(), "arial");
		break;
	case SDL_MOUSEBUTTONDOWN:
		// reset ss for each label
		ss.str("");
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
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, backgroundText, nullptr, nullptr);
	start.draw();
	tutorial.draw();
	setting.draw();
	SDL_RenderPresent(Game::renderer);
}
