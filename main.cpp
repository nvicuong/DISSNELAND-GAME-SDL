#include "Game.h"
#include "Menu.h"

Game *game = nullptr;
Menu* menu = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	

	game = new Game();
	menu = new Menu();
	game->init("DISSNELAND", MAX_WIDTH_SCREEN, MAX_HEIGHT_SCREEN, false);
	menu->init();
	while (game->running())
	{
		
		frameStart = SDL_GetTicks();
		if (Game::isRunningMenu)
		{
			menu->handleEvents();
			menu->render();
		}
		else
		{
			if (Game::resetGame)
			{
				game->initObject();
			}
		game->handleEvents();
		game->update();
		game->render();
		}
		// game->handleEvents();
		// game->update();
		// game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}