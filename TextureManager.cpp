#include "TextureManager.h";

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
/*The function TextureManager::LoadTexture(const char* texture) takes a const char* parameter representing the path to an image file and returns an SDL_Texture*.*/

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
/*The SDL_RenderCopyEx function is used to copy a portion of a texture to the current rendering target with the ability to rotate and/or flip the texture.

The function takes in the following parameters:

renderer: the rendering context
texture: the texture to be copied
srcRect: a pointer to the source rectangle, which is the portion of the texture to be copied. If null, the entire texture is copied
dstRect: a pointer to the destination rectangle, which is the location where the texture will be copied to
angle: the angle of rotation in degrees. Positive values rotate clockwise, negative values rotate counterclockwise. The default is 0.
center: a pointer to the center point of rotation. The default is null, which means the rotation will be done around the center of the destination rectangle.
flip: a set of flags used to flip the texture horizontally and/or vertically. The default is SDL_FLIP_NONE, which means no flipping.*/