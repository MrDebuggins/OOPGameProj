#pragma once
#include "menu.h"
class pauseMenu : public menu
{
private:
	bool active[2];
public:
	void loadTextures(SDL_Renderer* rend);
	void draw(SDL_Renderer* rend);
	int buttonPressed(SDL_Event* e);

	pauseMenu() 
	{
		active[0] = false;
		active[1] = false;
	}

	~pauseMenu(){}
};

