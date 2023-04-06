#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	

	std::cout << 2;
	game = new Game();
	game->init("DISSNELANDD", MAX_WIDTH_SCREEN, MAX_HEIGHT_SCREEN, false);

	while (game->running())
	{
		
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}