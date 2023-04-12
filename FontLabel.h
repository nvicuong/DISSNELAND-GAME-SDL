#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontLabel : public Component
{
public:
	FontLabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetlabelText(labelText, labelFont);
	}
	~FontLabel()
	{}

	void SetlabelText(std::string text, std::string font)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);

	}
	void draw() override
	{
	SD:SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;

};