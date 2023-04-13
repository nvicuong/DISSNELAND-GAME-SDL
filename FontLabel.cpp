#pragma once

#include "FontLabel.h"

FontLabel::FontLabel(int xpos, int ypos, std::string text) :
		labelText(text)
	{
		position.x = xpos;
		position.y = ypos;
        textColor.r = 255;
        textColor.g = 255;
        textColor.b = 255;
        textColor.a = 255;
		labelTexture = NULL;
	}
bool FontLabel::SetlabelText(TTF_Font* font)
	{
        // std::cout << 5;
		SDL_Surface* surf = TTF_RenderText_Solid(font, labelText.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        // std::cout << (surf != NULL) ;
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
        return labelTexture != NULL;
	}
void FontLabel::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;
}

void FontLabel::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0, 255};
        textColor = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255, 255};
        textColor = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0, 255};
        textColor = color;
    }
}
