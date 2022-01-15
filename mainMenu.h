#pragma once
#include "menu.h"
class mainMenu : public menu
{
private:
	bool active[4];
public:
	void loadTextures(SDL_Renderer* rend);
	void draw(SDL_Renderer* rend);
	int buttonPressed(SDL_Event* e);
	bool isIn() { return in; }

	mainMenu()
	{
		active[0] = false;
		active[1] = false;
		active[2] = false;
		active[3] = false;
	}

	~mainMenu()	{}
};

