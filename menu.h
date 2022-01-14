#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"

class menu
{
protected:
	SDL_Texture** buttonsTextures;
	SDL_Rect* buttonHitBoxes;
	bool in = false;

public:
	virtual void loadTextures(SDL_Renderer* rend) = 0;
	virtual int eventHandler(SDL_Event* e, SDL_Renderer* rend) = 0;
	virtual void draw(SDL_Renderer* rend) = 0;
	bool isIn() { return in; }
	void setIn(bool in) { this->in = in; }
	virtual int buttonPressed(SDL_Event* e) = 0;

	//void loadTextures(SDL_Renderer* rend);
	//int eventHandler(SDL_Event* e, SDL_Renderer* rend);
	//void draw(SDL_Renderer* rend);
	//bool isIn() { return in; }
	//int buttonPressed(SDL_Event* e);
	
};

