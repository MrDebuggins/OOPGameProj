#pragma once
#include "animatedGameObj.h"
class entity : public animatedGameObj
{
protected:
	int xVelocity; 
	int yVelocity;
	int viewDirection;
	int HP;
	int lastShootTime;

public:
	entity() 
	{
		xVelocity = 0;
		yVelocity = 0;
		viewDirection = 0;
		HP = 0;
		lastShootTime = 0;
	}

	~entity() 
	{
		xVelocity = NULL;
		yVelocity = NULL;
		viewDirection = NULL;
		HP = NULL;
	}
};

