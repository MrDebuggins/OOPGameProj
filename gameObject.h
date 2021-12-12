#pragma once
#include <SDL.h>
#include "dataStructures.h"
//#include "level.h"
class gameObject
{
protected:
	objType type;
	SDL_Rect shape;

public:
	gameObject() 
	{
		shape = { 0,0,0,0 };
		type = objTypeDefault;
	}
};

