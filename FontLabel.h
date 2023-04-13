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
	FontLabel(int xpos, int ypos, std::string text);
	~FontLabel()
	{}

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2
	};

	bool SetlabelText(TTF_Font* font);
	void draw() override
	{
	SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}
	void destroy()
	{
		SDL_DestroyTexture(labelTexture);
		labelTexture = NULL;
	}
	
	void SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void setColor(int type);

	void SetText(const std::string& text) { labelText = text; }
	std::string GetText() const {return labelText; }


private:
	SDL_Rect position;
	std::string labelText;
	SDL_Texture* labelTexture;
	SDL_Color textColor;
	// std::string labelFont;

};