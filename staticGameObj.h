#pragma once
#include "gameObject.h"
class staticGameObj:public gameObject
{
	SDL_Texture* objTexture;

public:
	staticGameObj() 
	{
		objTexture = NULL;
	}

	~staticGameObj() 
	{
		objTexture = NULL;
	}

	void loadStaticObjTexture(const char path[], SDL_Renderer* rend);
	void drawStaticObj(SDL_Renderer* rend);
	void setObjHitBox(SDL_Rect r);
};

