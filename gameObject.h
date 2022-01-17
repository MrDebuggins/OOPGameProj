#pragma once
#include <SDL.h>
#include "dataStructures.h"

class gameObject
{
protected:
	SDL_Rect shape;

public:
	gameObject() 
	{
		shape = { 0,0,0,0 };
	}

	~gameObject() {}

	SDL_Rect* getHitBox() { return &shape; }
};

