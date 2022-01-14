#pragma once
#include "animatedGameObj.h"
#include "dataStructures.h"
#include "effect.h"
class projectile : public animatedGameObj
{
	SDL_Texture* projTexture = NULL;
	projectileTypes type;
	bool show = 0;
	int damage;
	int viewDir;

	effect* shellEffect;
public:
	projectile() 
	{
		projTexture = NULL;
		this->viewDir = 0;
		type = bullet;
		shape = { -300,-300,6,16 };
		damage = 0;
		shellEffect = NULL;
	}
	~projectile() 
	{
		delete projTexture;
		delete shellEffect;
		animatedGameObj::~animatedGameObj();
	}

	void setExistFlag(bool f, int viewDir, int posx, int posy);
	bool getExistFlag();
	void loadTexture(SDL_Renderer* rend);
	void setType(int type);
	bool mapCollision();
	int objCollision(SDL_Rect* obj);
	void move();
	void draw(SDL_Renderer* rend);
	SDL_Rect* getHitBox() { return &shape; }
	int getViewDir() { return viewDir; }
};

