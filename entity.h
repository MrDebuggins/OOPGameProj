#pragma once
#include "animatedGameObj.h"
class entity : public animatedGameObj
{
protected:
	int xVelocity; 
	int yVelocity;
	int HP;
	int lastShootTime;

public:
	entity() 
	{
		xVelocity = 0;
		yVelocity = 0;
		HP = 0;
		lastShootTime = 0;
	}

	~entity() 
	{
		for (int i = 0; i < 2; i++) 
		{
			SDL_DestroyTexture(texturesArray[i]);
		}
	}
};

