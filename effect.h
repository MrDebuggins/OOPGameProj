#pragma once
#include "animatedGameObj.h"

class effect : public animatedGameObj
{
	bool type;
	bool active;

public:
	effect(bool type, int x, int y, SDL_Renderer* rend, bool active)
	{
		this->type = type;
		shape.x = x;
		shape.y = y;
		this->active = active;

		loadTexutres(rend);
	}

	~effect() 
	{
		for (int i = 0; i < 8; i++) 
		{
			SDL_DestroyTexture(texturesArray[i]);
		}
	}

	void loadTexutres(SDL_Renderer* rend);
	bool draw(SDL_Renderer* rend);
	void activate(int x, int y);
};

