#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"

class menu
{
protected:
	SDL_Texture** buttonsTextures;
	SDL_Rect* buttonHitBoxes;
	bool in;

public:
	virtual void loadTextures(SDL_Renderer* rend) = 0;
	virtual void draw(SDL_Renderer* rend) = 0;
	bool isIn() { return in; }
	void setIn(bool in) { this->in = in; }
	virtual int buttonPressed(SDL_Event* e) = 0;

	menu()
	{
		buttonsTextures = NULL;
		buttonHitBoxes = NULL;
		in = false;
	}

	~menu() 
	{
		delete[] buttonHitBoxes;
		for (int i = 0; i < 8; i++) 
		{
			if (buttonsTextures[i] != NULL) 
			{
				SDL_DestroyTexture(buttonsTextures[i]);
			}
			else 
			{
				break;
			}
		}
	}
};

