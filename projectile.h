#pragma once
#include "animatedGameObj.h"
class projectile : public animatedGameObj
{
	SDL_Texture* projTexture = NULL;
	bool show = 0;
public:
	//projectile() 
	//{
	//	projTexture = NULL;
	//}

	void setVelocity(int v);
};

