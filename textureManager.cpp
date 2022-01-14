#include "textureManager.h"
#include "Game.h"

SDL_Texture* textureManager::loadTexture(const char* path, SDL_Renderer* rend) 
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL)
		SDL_Log("Cannot load texture from path: %s. SDL_Error: %s", path, SDL_GetError());

	return texture;
}

void textureManager::drawTexture(SDL_Texture* source, SDL_Rect* dest, SDL_Renderer* rend, SDL_Rect* shape, int angle) 
{
	try
	{
		SDL_RenderCopyEx(rend, source, NULL, shape, angle, NULL, SDL_FLIP_NONE);
	}
	catch (const std::exception&)
	{
		SDL_Log("SDL_Error: %s", SDL_GetError());
	}
	
	//SDL_Log("SDL_Error: %s", SDL_GetError());
}