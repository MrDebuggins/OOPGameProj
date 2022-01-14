#pragma once
#include "gameObject.h"
class animatedGameObj :public gameObject
{
protected:
	SDL_Texture** texturesArray;

	int velocity;
	int viewDirection;
	int animID;

public:
	animatedGameObj() 
	{
		texturesArray = NULL;

		velocity = 2;
		viewDirection = 0;
		animID = 0;
	}

	~animatedGameObj() 
	{
		delete[] texturesArray;
		texturesArray = NULL;
		velocity = NULL;
		animID = NULL;
	}
};

