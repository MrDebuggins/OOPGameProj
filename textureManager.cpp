#include "textureManager.h"
#include "Game.h"

SDL_Texture* textureManager::loadTexture(const char* path, SDL_Renderer* rend) 
{
	SDL_Texture* texture = NULL;

	try 
	{
		SDL_Surface* surface = IMG_Load(path);
		texture = SDL_CreateTextureFromSurface(rend, surface);
		SDL_FreeSurface(surface);
		if (texture == NULL) 
		{
			throw SDL_GetError();
		}
	}catch(const char* error)
	{
		SDL_Log("Cannot load texture from path: %s. SDL_Error: %s", path, error);
	}
	
	return texture;
}

void textureManager::drawTexture(SDL_Texture* source, SDL_Rect* dest, SDL_Renderer* rend, SDL_Rect* shape, int angle) 
{
	try
	{
		if (SDL_RenderCopyEx(rend, source, NULL, shape, angle, NULL, SDL_FLIP_NONE)) 
		{
			throw;
		}
	}
	catch (...)
	{
		SDL_Log("Error rendering texture. SDL_Error: %s", SDL_GetError());
	}
}