#pragma once
#include <SDL.h>
#include <SDL_image.h>
class textureManager
{
public:
	static SDL_Texture* loadTexture(const char* path, SDL_Renderer* rend);
	static void drawTexture(SDL_Texture* source, SDL_Rect* dest, SDL_Renderer* rend, SDL_Rect* shape, int angle);
	//static SDL_Texture** textures;
};

