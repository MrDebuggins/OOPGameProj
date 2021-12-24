#pragma once
#include "animatedGameObj.h"
class entity : public animatedGameObj
{
protected:
	int xVelocity; 
	int yVelocity;
	int viewDirection;

public:
	entity() 
	{
		xVelocity = 0;
		yVelocity = 0;
		viewDirection = 0;
	}
};

