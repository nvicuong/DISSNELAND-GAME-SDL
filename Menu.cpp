#include "Menu.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Components.h"
#include <sstream>


SDL_Event Menu::event;
bool Menu::isRunning = 1;
TTF_Font* fontMenu = NULL;

FontLabel start(30, 30, "start");
FontLabel tutorial(60, 60, "tutorial");
FontLabel setting(90, 90, "setting");
void Menu::init()
{
	// backgroundText = TextureManager::LoadTexture("assets/menu.png");
	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	fontMenu = TTF_OpenFont("assets/arial.ttf", 30);

	start.SetlabelText(fontMenu);
	start.setColor(FontLabel::BLACK_TEXT);

	tutorial.SetlabelText(fontMenu);
	tutorial.setColor(FontLabel::WHITE_TEXT);

	setting.SetlabelText(fontMenu);
	setting.setColor(FontLabel::WHITE_TEXT);
	// assetsMenu->AddFont("arial", "assets/arial.ttf", 32);
	// SDL_Color WHITE = {255, 255, 255, 255};
	// start.addComponent<FontLabel>(20, 20, "START", "arial", WHITE);
	// tutorial.addComponent<FontLabel>(30, 30, "TUTORIAL", "arial", WHITE);
	// setting.addComponent<FontLabel>(40, 40, "SETTING", "arial",  WHITE);
	// SDL_RenderCopy(Game::renderer, backgroundText, nullptr, nullptr);
	
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
		// start.getComponent<FontLabel>().destroy();
		ss.str("");
		ss << "mouse position: " << event.motion.x << " , " << event.motion.y;
		// start.getComponent<FontLabel>().SetlabelText(ss.str(), "arial");
		start.destroy();
		start.SetText(ss.str());
		start.SetlabelText(fontMenu);
		break;
	case SDL_MOUSEBUTTONDOWN:
		// reset ss for each label
		// ss.str("");
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_f)
		{
			isRunning = 0;
		}
		break;
	case SDL_QUIT:
		Game::isRunning = false;
		break;
	default:
		break;
}
	return 1;
}

void Menu::render()
{
	SDL_RenderClear(Game::renderer);
	// SDL_RenderCopy(Game::renderer, backgroundText, nullptr, nullptr);
	start.draw();
	tutorial.draw();
	setting.draw();
	SDL_RenderPresent(Game::renderer);
}
